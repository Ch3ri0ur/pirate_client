const express = require('express');
const cors = require('cors');
const SerialPort = require('serialport');

// TODO: Get config from Arduino
clientSendBuffer = {};
clientSendBuffer_config = {
    0: { name: 'p_val', type: 'float' }, // ? description? or identifier / name , max , min
    1: { name: 'i_val', type: 'float' },
    2: { name: 'd_val', type: 'float' },
    3: { name: 'control_val', type: 'float' },
    4: { name: 'measurement', type: 'float' },
};
arduinoSendBuffer = {};
arduinoSendBuffer_config = {
    0: { name: 'p', type: 'float' },
    1: { name: 'i', type: 'float' },
    2: { name: 'd', type: 'float' },
    3: { name: 'stop', type: 'bool' },
    4: { name: 'start', type: 'bool' },
};
// arduinoSendBuffer_datatypes = [
//     'int',
//     'uint',
//     'long',
//     'ulong',
//     'float',
//     'double',
//     'byte',
//     'word',
//     'bool',
//     'char',
//     'string',
// ];

// $(1char for id)(1char for datatype)((+-)Digitamount of chars)E((+-)Expamount of chars)#%
// $(1char for id)(1char for datatype)((+-)Digitamount of chars)E((+-)Expamount of chars)#(1id)(1datatype)((+-)Digitamount of chars)E((+-)Expamount of chars)#%

SerialPort.list()
    .then((result) => {
        console.log(result);
        if (result && result.length > 0) {
            const port = new SerialPort(result[0].path, {
                baudRate: 115200,
            });
            const Delimiter = require('@serialport/parser-delimiter');
            const parser = port.pipe(
                new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
            );
            parser.on('data', (buffer) => {
                let controlbyte = buffer[0];
                let data = buffer.slice(1);
                if (controlbyte == 77) {
                    // M Debug Message
                    console.log('Debug: ' + data.toString());
                } else if (controlbyte == 82) {
                    // R Request Data
                    // console.log("request")
                    if (Object.entries(arduinoSendBuffer).length !== 0) {
                        entry = Object.entries(arduinoSendBuffer)[0];
                        delete arduinoSendBuffer[entry[0]];
                        console.log(entry);
                        let payload;
                        let buf;
                        // TODO Check if the type is compatible with config
                        switch (arduinoSendBuffer_config[entry[0]].type) {
                            case 'int':
                                buf = Buffer.alloc(3);
                                buf.writeInt16LE(entry[1], 1);
                                break;
                            case 'uint':
                                buf = Buffer.alloc(3);
                                buf.writeUInt16LE(entry[1], 1);
                                break;
                            case 'long':
                                buf = Buffer.alloc(5);
                                buf.writeInt32LE(entry[1], 1);
                                break;
                            case 'ulong':
                                buf = Buffer.alloc(5);
                                buf.writeUInt32LE(entry[1], 1);
                                break;
                            case 'float':
                                buf = Buffer.alloc(5);
                                buf.writeFloatLE(entry[1], 1);
                                break;
                            case 'double':
                                buf = Buffer.alloc(5);
                                buf.writeFloatLE(entry[1], 1);
                                break;
                            case 'byte':
                                buf = Buffer.alloc(2);
                                buf.writeUInt8(entry[1], 1);
                                break;
                            case 'word':
                                buf = Buffer.alloc(3);
                                buf.writeUInt16LE(entry[1], 1);
                                break;
                            case 'bool':
                                buf = Buffer.alloc(2);
                                buf.writeUInt8(entry[1], 1);
                                break;
                            case 'char':
                                buf = Buffer.alloc(2);
                                buf.write(entry[1], 1, 'ascii');
                                break;
                            case 'string':
                                buf = Buffer.alloc(entry[1].length + 2);
                                buf[buf.byteLength - 1] = 00;
                                buf.write(entry[1], 1, 'ascii');
                                break;
                        }
                        buf[0] = parseInt(entry[0]) + 48;
                        console.log(buf);
                        port.write(buf);
                    } else {
                        console.log('nothing to send');
                        let buf = Buffer.alloc(1);
                        buf[0] = 0x29;
                        port.write(buf);
                    }
                } else {
                    let index = buffer[1];
                    data = buffer.slice(2);
                    //console.log('-------- new var ------');
                    //console.log(data);
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
        } else {
            throw Error('No port found is the Arduino attached?');
        }
    })
    .catch((reason) => {
        console.log(reason);
        throw Error('Something went wrong with the Arduino communication');
    });

const app = express();

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
    data = JSON.parse(req.body);
    console.log(data);
    for (let [idx, value] of Object.entries(data)) {
        console.log(`${idx}: ${value}`);
        // TODO perhaps check if value matches type
        arduinoSendBuffer[idx] = value
    };
    // add stuff to arduinoSendBuffer
    res.send('success');
});

app.use(cors());

const PORT = 3000;

app.listen(PORT, () => console.log(`The server is listening on port ${PORT}`));
