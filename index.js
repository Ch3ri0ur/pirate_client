const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const SerialPort = require('serialport');
const Delimiter = require('@serialport/parser-delimiter');
const Readyparser = require('@serialport/parser-ready');

clientSendBuffer = {};
clientSendBuffer_config = {};
arduinoSendBuffer = new Map();
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
        // Wait for a start sequence to flush out the Buffers
        const readyparser = port.pipe(
            new Readyparser({ delimiter: new Uint8Array([0xee, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
        );
        // Forward Chunks separated by a \xffPirAtE\n to .on data events
        const parser = readyparser.pipe(
            new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
        );
        // TODO FLUSH THE STREAM TILL DATATYPESIZES
        parser.on('data', (buffer) => {
            switch (buffer[0]) {
                case 82: // R Request Data
                    requestDataHandler(port);
                    break;
                case 77: // M Debug Message
                    const data = buffer.slice(1);
                    console.log('Debug: ' + data.toString());
                    break;
                case 80: // P arduino datatype sizes
                    //console.log(data);
                    arduinoDatatypeSizesHandler(buffer);
                    console.log(arduinoDatatypeSizes);
                    break;
                case 84: // T arduino -> node config string
                    arduinoToNodeConfigHandler(buffer);
                    console.log(clientSendBuffer_config);
                    break;
                case 116: // t node -> arduino config string
                    nodeToArduinoConfigHandler(buffer);
                    console.log(arduinoSendBuffer_config);
                    break;
                default:
                    // receive Data
                    receiveDataHandler(buffer);
            }
        });
    })
    .catch((e) => {
        console.error(e.message);
        process.exit(1);
    });

function arduinoDatatypeSizesHandler(buffer) {
    data = buffer.slice(1);
    datatypeSizeBufferValues = [...data.values()];
    let i = 0;
    for (i = 0; i < datatypeSizeBufferValues.length; i = i + 3) {
        arduinoDatatypeSizes[String.fromCharCode(datatypeSizeBufferValues[i])] = datatypeSizeBufferValues[i + 1];
    }
}

function arduinoToNodeConfigHandler(buffer) {
    const configString = buffer.slice(2).toString();
    const configComponents = configString.split('$');
    //console.log(configComponents);
    // index$name$type
    if (configComponents.length === 3) {
        const id = buffer[1] - 48;
        clientSendBuffer_config[id] = {
            name: configComponents[1],
            type: configComponents[2],
        };
    }
}

function nodeToArduinoConfigHandler(buffer) {
    const configString = buffer.slice(2).toString();
    // index$name$type$default$max$min
    const configComponents = configString.split('$');
    // Float and double can not be serial printed with values exceeding ulong (would print "ovf")
    if (configComponents.length === 6) {
        const id = buffer[1] - 48;
        arduinoSendBuffer_config[id] = {
            name: configComponents[1],
            type: configComponents[2],
            // TODO default, max, min values stored as strings as of now.. perhaps change
            default: Number(configComponents[3]),
            max: Number(configComponents[4]),
            min: Number(configComponents[5]),
        };
    }
}

function receiveDataHandler(buffer) {
    let index = buffer[1];
    data = buffer.slice(2);
    // If this logging is activated performance degrades drastically
    //console.log(Date.now());
    //console.log(buffer);
    let value = undefined;
    // ? Is it necessary to send type if config was declared beforehand?
    // TODO Sanitize Bufferlength. Readfunc errors with not matching buffer length
    switch (buffer[0]) {
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
    if (value !== undefined) {
        // if data is to be sent add to send buffer
        //console.log(value);
        ts = Date.now();
        const id = index - 48;
        if (!clientSendBuffer[ts]) {
            clientSendBuffer[ts] = {};
        }
        clientSendBuffer[ts][id] = value;
    }
}

function requestDataHandler(port) {
    if (arduinoSendBuffer.size === 0) {
        let buf = Buffer.allocUnsafe(1);
        buf[0] = 0x29;
        port.write(buf);
        console.log('no data to Send');
    } else {
        // console.log(arduinoSendBuffer);
        let buf = new Buffer.alloc(64);
        let runningSize = 0;
        for (let [key, value] of arduinoSendBuffer) {
            if (!(key in arduinoSendBuffer_config)) {
                arduinoSendBuffer.delete(key);
                continue;
            }
            let type = arduinoSendBuffer_config[key].type;
            let size;
            if (type === 'S') {
                let maxAllowedSize = arduinoSendBuffer_config[key].max;
                if (value.length > maxAllowedSize) {
                    value = value.slice(0, maxAllowedSize);
                }
                size = value.length + 1; //end byte + id byte
            } else {
                size = arduinoDatatypeSizes[type]; // + id byte
            }
            if (runningSize + size + 1 < buf.length) {
                buf[runningSize] = parseInt(key) + 48;
                runningSize += 1;

                switch (type) {
                    case 'I':
                        buf.writeInt16LE(value, runningSize);
                        break;
                    case 'U':
                        buf.writeUInt16LE(value, runningSize);
                        break;
                    case 'L':
                        buf.writeInt32LE(value, runningSize);
                        break;
                    case 'u':
                        buf.writeUInt32LE(value, runningSize);
                        break;
                    case 'F':
                        buf.writeFloatLE(value, runningSize);
                        break;
                    case 'D':
                        buf.writeFloatLE(value, runningSize);
                        break;
                    case 'B':
                        buf.writeUInt8(value, runningSize);
                        break;
                    case 'W':
                        buf.writeUInt16LE(value, runningSize);
                        break;
                    case 'b':
                        buf.writeUInt8(value, runningSize);
                        break;
                    case 'C':
                        buf.write(value, runningSize, 'ascii');
                        break;
                    case 'S':
                        //buf = Buffer.alloc(keyValuePair[1].length + 2);
                        buf[runningSize + size + 1] = 00; // ! TEST THIS
                        buf.write(value, runningSize, 'ascii');
                        break;
                }
                runningSize = runningSize + size;
                arduinoSendBuffer.delete(key);
            }
        }
        console.log(buf);
        buf = buf.slice(0, runningSize);
        port.write(buf);
    }
}

const app = express();
app.use(helmet()); // TODO test if this creates problems

app.use(express.json());

app.get('/getconfig', (req, res) => {
    console.log(req);
    console.log(clientSendBuffer_config);
    console.log(arduinoSendBuffer_config);
    console.log(arduinoDatatypeSizes);
    res.json({
        clientsend_config: clientSendBuffer_config,
        arduinosend_config: arduinoSendBuffer_config,
        arduinoDatatypeSizes: arduinoDatatypeSizes,
    });
});

let clients = {};
let counter = 0;

app.get('/stream', (req, res) => {
    res.set({
        'Content-Type': 'text/event-stream',
        'Cache-Control': 'no-cache',
        Connection: 'keep-alive',

        // enabling CORS
        'Access-Control-Allow-Origin': '*',
        'Access-Control-Allow-Headers': 'Origin, X-Requested-With, Content-Type, Accept',
    });
    console.log('event source started id:' + counter);
    let mycount = counter;
    res.socket.on('end', (e) => {
        console.log('event source closed id:' + mycount);
        delete clients[mycount];
        res.end();
    });
    clients[counter] = res;
    counter++;
});

var intervalID = setInterval(() => {
    //   console.log(clientSendBuffer);
    if (Object.entries(clientSendBuffer).length !== 0) {
        for (let [key, res] of Object.entries(clients)) {
            res.write('event: message\n');
            res.write('data: ' + JSON.stringify(clientSendBuffer) + '\n\n');
        }
        clientSendBuffer = {};
    } else {
        // nothing to send
    }
}, 100);

app.post('/ctrl', (req, res) => {
    console.log(req);
    data = req.body; // ! is this necessary? above i use express.json()
    console.log(data);
    let success = true;
    for (let [idx, value] of Object.entries(data)) {
        console.log(`${idx}: ${value}`);
        if (idx in arduinoSendBuffer_config) {
            let type = arduinoSendBuffer_config[idx].type;
            if (type === 'S' || type === 'C') {
                if (typeof value === 'string') {
                    arduinoSendBuffer.set(idx, value);
                } else {
                    success = false;
                }
            } else if (type) {
                if (typeof value === 'number') {
                    arduinoSendBuffer.set(idx, value);
                } else {
                    success = false;
                }
            }
        }
    }
    if (success) {
        res.sendStatus(200);
    } else {
        res.sendStatus(400);
    }
    // TODO perhaps check if value matches type and range
});

app.use(cors());

const PORT = 9876;

app.listen(PORT, () => console.log(`The server is listening on port ${PORT}`));
