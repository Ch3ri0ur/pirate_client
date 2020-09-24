const express = require('express');
const cors = require('cors');
const SerialPort = require('serialport');
const helmet = require('helmet');

// TODO: Get config from Arduino
clientSendBuffer = {};
clientSendBuffer_config = {};
arduinoSendBuffer = {};
arduinoSendBuffer_config = {};
arduinoDatatypeSizes = {};

// outputs the path to an arduino or nothing
async function findArduino() {
    const ports = await SerialPort.list();
    for (const port of ports) {
        if (/arduino/i.test(port.manufacturer)) {
            return port.path;
        }
    }
    throw new Error(
        'No arduinos found. You must specify a port to load.\n\nFor example:\n\tserialport-repl COM3\n\tserialport-repl /dev/tty.my-serialport',
    );
}

findArduino()
    .then((portName) => {
        const port = new SerialPort(portName, {
            baudRate: 115200,
        });

        const Delimiter = require('@serialport/parser-delimiter');
        const Readyparser = require('@serialport/parser-ready');

        const readyparser = port.pipe(
            new Readyparser({ delimiter: new Uint8Array([0xee, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
        );
        const parser = readyparser.pipe(
            new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
        );

        parser.on('data', (buffer) => {
            let controlbyte = buffer[0];
            let data = buffer.slice(1);
            switch (controlbyte) {
                case 77:
                    // M Debug Message
                    console.log('Debug: ' + data.toString());
                    break;
                case 80: // P arduino datatype sizes
                    configString = data.toString();
                    configComponents = configString.split('$');
                    for (comp in configComponents) {
                        arduinoDatatypeSizes[comp[0]] = comp[1].charCodeAt(0);
                    }
                    console.log(arduinoDatatypeSizes);
                    break;
                case 84: // T arduino -> node config string
                    configString = data.toString();
                    configComponents = configString.split('$');
                    // index$name$type
                    clientSendBuffer_config[configComponents[0]] = {
                        name: configComponents[1],
                        type: configComponents[2],
                    };
                    console.log(clientSendBuffer_config);
                    break;
                case 116: // t node -> arduino config string
                    configString = data.toString();
                    configComponents = configString.split('$');
                    // index$name$type$default$max$min
                    arduinoSendBuffer_config[configComponents[0]] = {
                        name: configComponents[1],
                        type: configComponents[2],
                        default: configComponents[3],
                        max: configComponents[4],
                        min: configComponents[5],
                    };
                    console.log(arduinoSendBuffer_config);
                    break;
                case 82:
                    // R Request Data
                    // console.log("request")
                    if (Object.entries(arduinoSendBuffer).length !== 0) {
                        entry = Object.entries(arduinoSendBuffer)[0];
                        delete arduinoSendBuffer[entry[0]];
                        console.log(entry);
                        let payload;
                        let buf;
                        // TODO Check if the type is compatible with config
                        let payload_size = arduinoDatatypeSizes[arduinoSendBuffer_config[entry[0]].type] + 1;
                        switch (arduinoSendBuffer_config[entry[0]].type) {
                            case 'I':
                                buf = Buffer.alloc(3);
                                buf.writeInt16LE(entry[1], 1);
                                break;
                            case 'U':
                                buf = Buffer.alloc(3);
                                buf.writeUInt16LE(entry[1], 1);
                                break;
                            case 'L':
                                buf = Buffer.alloc(5);
                                buf.writeInt32LE(entry[1], 1);
                                break;
                            case 'u':
                                buf = Buffer.alloc(5);
                                buf.writeUInt32LE(entry[1], 1);
                                break;
                            case 'F':
                                buf = Buffer.alloc(5);
                                buf.writeFloatLE(entry[1], 1);
                                break;
                            case 'D':
                                buf = Buffer.alloc(5);
                                buf.writeFloatLE(entry[1], 1);
                                break;
                            case 'B':
                                buf = Buffer.alloc(2);
                                buf.writeUInt8(entry[1], 1);
                                break;
                            case 'W':
                                buf = Buffer.alloc(3);
                                buf.writeUInt16LE(entry[1], 1);
                                break;
                            case 'b':
                                buf = Buffer.alloc(2);
                                buf.writeUInt8(entry[1], 1);
                                break;
                            case 'C':
                                buf = Buffer.alloc(2);
                                buf.write(entry[1], 1, 'ascii');
                                break;
                            case 'S':
                                buf = Buffer.alloc(entry[1].length + 2);
                                buf[buf.byteLength - 1] = 00;
                                buf.write(entry[1], 1, 'ascii');
                                break;
                        }
                        buf[0] = parseInt(entry[0]) + 48;
                        console.log(`Sending to Arduino created payload_size ${payload_size}`);
                        console.log(buf);
                        port.write(buf);
                    } else {
                        console.log('nothing to send');
                        let buf = Buffer.allocUnsafe(1);
                        buf[0] = 0x29;
                        port.write(buf);
                    }
                    break;
                default:
                    // receive Data
                    let index = buffer[1];
                    data = buffer.slice(2);
                    let value;
                    // ? Is it necessary to send type if config was declared beforehand?
                    switch (controlbyte) {
                        case 66: // B Byte
                            value = data.readUIntLE(0, data.length);
                            //console.log('byte: ' + value);
                            break;
                        case 67: // C char
                            value = data.toString();
                            //console.log('char: ' + value);
                            break;
                        case 68: // D double
                            value = data.readFloatLE();
                            //console.log('double: ' + value);
                            break;
                        case 70: // F float
                            value = data.readFloatLE();
                            //console.log('float: ' + value);
                            break;
                        case 73: // I int
                            value = data.readIntLE(0, data.length);
                            //console.log('got int: ' + value);
                            break;
                        case 76: // L long
                            value = data.readIntLE(0, data.length);
                            //console.log('long: ' + value);
                            break;
                        case 83: // S string
                            value = data.toString();
                            //console.log('String: ' + value);
                            break;
                        case 85: // U unsigned int
                            value = data.readUIntLE(0, data.length);
                            //console.log('uint: ' + value);
                            break;
                        case 87: // W word
                            value = data.readUIntLE(0, data.length);
                            //console.log('word: ' + value);
                            break;
                        case 98: // b boolean
                            value = data.readUInt8() ? true : false;
                            //console.log('Boolean: ' + value);
                            break;
                        case 117: // u unsigned long
                            value = data.readUIntLE(0, data.length);
                            //console.log('ulong: ' + value);
                            break;
                        default:
                            console.log('----------- Fallthrough, unknown controlbyte ----------');
                            console.log(controlbyte);
                            console.log(data);
                            value = null;
                    }
                    if (value) {
                        // if data is to be sent add to send buffer
                        console.log(value);
                        ts = Date.now();
                        if (clientSendBuffer[ts]) {
                            clientSendBuffer[ts] = [...clientSendBuffer[ts], { i: index - 48, v: value }];
                        } else {
                            clientSendBuffer[ts] = [{ i: index - 48, v: value }];
                        }
                    }
            }
        });
    })
    .catch((e) => {
        console.error(e.message);
        process.exit(1);
    });

const app = express();
app.use(helmet()); // TODO test if this creates problems

app.use(express.json());

app.get('/getconfig', (req, res) => {
    console.log(req);
    console.log(arduinoSendBuffer_config);
    console.log(clientSendBuffer_config);
    res.json({
        clientsend_config: clientSendBuffer_config,
        arduinosend_config: arduinoSendBuffer_config,
    });
});

app.get('/stream', (req, res) => {
    res.set({
        'Content-Type': 'text/event-stream',
        'Cache-Control': 'no-cache',
        Connection: 'keep-alive',

        // enabling CORS
        'Access-Control-Allow-Origin': '*',
        'Access-Control-Allow-Headers': 'Origin, X-Requested-With, Content-Type, Accept',
    });

    var intervalID = setInterval(() => {
        //   console.log(clientSendBuffer);
        if (Object.entries(clientSendBuffer).length !== 0) {
            // send stuff
            console.log(clientSendBuffer);
            res.write('event: message\n');
            res.write('data: ' + JSON.stringify(clientSendBuffer) + '\n');
            // console.log(JSON.stringify(clientSendBuffer));
            clientSendBuffer = {};
        } else {
            // nothing to send
        }
    }, 100);
});

app.post('/ctrl', (req, res) => {
    console.log(req);
    data = JSON.parse(req.body); // ! is this necessary? above i use express.json()
    console.log(data);
    for (let [idx, value] of Object.entries(data)) {
        console.log(`${idx}: ${value}`);
        // TODO perhaps check if value matches type
        arduinoSendBuffer[idx] = value;
    }
    // add stuff to arduinoSendBuffer
    res.send('success');
});

app.use(cors());

const PORT = 3000;

app.listen(PORT, () => console.log(`The server is listening on port ${PORT}`));
