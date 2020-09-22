const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('COM3', {
    baudRate: 115200,
});
// const parser = port.pipe(new Readline({ delimiter: '\r\n' }))

clientSendBuffer = {};
arduinoSendBuffer_datatypes = [
    'int',
    'uint',
    'long',
    'ulong',
    'float',
    'double',
    'byte',
    'word',
    'bool',
    'char',
    'string',
];
arduinoSendBuffer_template = {
    0: -33,
    1: 1,
    2: 33,
    3: 4,
    4: 33.5,
    5: 1.98,
    6: 33,
    7: 1,
    8: true,
    9: 'f',
    10: 'was willst',
};

arduinoSendBuffer = {};

//const ByteLength = require('@serialport/parser-byte-length')
const Delimiter = require('@serialport/parser-delimiter');
//const parser = port.pipe(new ByteLength({ length: 4 }))
const parser = port.pipe(
    new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
);

var testLoadID2 = setInterval(() => {
    //   console.log(clientSendBuffer);
    // console.log("reloading!!!!")
    if (Object.entries(arduinoSendBuffer_template).length !== 0) {
        // send stuff
        // console.log(JSON.stringify(clientSendBuffer));
        arduinoSendBuffer = JSON.parse(JSON.stringify(arduinoSendBuffer_template));
        // arduinoSendBuffer = Object.assign(arduinoSendBuffer_template);
    } else {
        // nothing to send
    }
}, 5000);
var testLoadID = setInterval(() => {
    //   console.log(clientSendBuffer);
    // console.log("reloading!!!!")
    if (Object.entries(arduinoSendBuffer_template).length !== 0) {
        // send stuff
        // console.log(JSON.stringify(clientSendBuffer));
        // arduinoSendBuffer = JSON.parse(JSON.stringify(arduinoSendBuffer_template));
        // arduinoSendBuffer = Object.assign(arduinoSendBuffer_template);
        const keys = Object.keys(arduinoSendBuffer_template);
        let randomIndex = keys[Math.floor(Math.random() * keys.length)];
        arduinoSendBuffer[randomIndex] = arduinoSendBuffer_template[randomIndex];
        randomIndex = keys[Math.floor(Math.random() * keys.length)];
        arduinoSendBuffer[randomIndex] = arduinoSendBuffer_template[randomIndex];
        console.log(arduinoSendBuffer);
    } else {
        // nothing to send
    }
}, 500);

var intervalID = setInterval(() => {
    //   console.log(clientSendBuffer);
    if (Object.entries(clientSendBuffer).length !== 0) {
        // send stuff
        console.log(clientSendBuffer);
        // console.log(JSON.stringify(clientSendBuffer));
        clientSendBuffer = {};
    } else {
        // nothing to send
    }
}, 100);
//const parser = port.pipe(new Delimiter({ delimiter: new Uint8Array([0xff, 'P', 'i', 'r', 'A', 't','E']) }))
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
            switch (arduinoSendBuffer_datatypes[entry[0]]) {
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
                    buf = Buffer.alloc(entry[1].length + 3);
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
        // port.write(Buffer(0x0)); //deprecation warning use the Buffer.alloc(), Buffer.allocUnsafe(), or Buffer.from() methods instead.
    } else {
        let index = buffer[1];
        data = buffer.slice(2);
        //console.log('-------- new var ------');
        //console.log(data);
        let value;
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
                console.log('----------- Fallthrough ----------');
                console.log(controlbyte);
                console.log(data);
                value = null;
        }
        ts = Date.now();
        if (clientSendBuffer[ts]) {
            clientSendBuffer[ts] = [...clientSendBuffer[ts], { i: index, v: value }];
        } else {
            clientSendBuffer[ts] = [{ i: index, v: value }];
        }
    }

    // l = 'P'.charCodeAt(0)
    // k = String.fromCharCode(0x15)

    // console.log("ID")
    // console.log(data[0])

    // if(data[0] == 0x29)
    // {
    //     console.log("Answer")
    //     respond = new Buffer.alloc(3)
    //     respond[0] = 0x30
    //     respond[1] = 0x0
    //     respond[2] = 0x0
    //     port.write(respond)
    //     console.log(respond[0])
    // }
});
