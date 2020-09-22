const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('COM3', {
    baudRate: 115200,
});
// const parser = port.pipe(new Readline({ delimiter: '\r\n' }))

//const ByteLength = require('@serialport/parser-byte-length')
const Delimiter = require('@serialport/parser-delimiter');
//const parser = port.pipe(new ByteLength({ length: 4 }))
const parser = port.pipe(
    new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45, 0x0a]) }),
);
//const parser = port.pipe(new Delimiter({ delimiter: new Uint8Array([0xff, 'P', 'i', 'r', 'A', 't','E']) }))
parser.on('data', (buffer) => {
    let controlbyte = buffer[0];
    let data = buffer.slice(1);
    // M Debug Message
    if (controlbyte == 77) {
        console.log('Debug: ' + data.toString());
    } else if (controlbyte == 82) {
        // R Request Data
        // port.write(Buffer(0x0)); //deprecation warning use the Buffer.alloc(), Buffer.allocUnsafe(), or Buffer.from() methods instead.
    } else {
        let index = buffer[1];
        data = buffer.slice(2);
        console.log("-------- new var ------")
        console.log(data);
        let value;
        switch (controlbyte) {
            case 66: // B Byte
                value = data.readUIntLE(0, data.length);
                console.log('byte: ' + value);
                break;
            case 67: // C char
                console.log('char: ' + data.toString());
                break;
            case 68: // D double
                let double = data.readFloatLE();
                console.log("double: " + double);
                break;
            case 70: // F float
                let float = data.readFloatLE();
                console.log("float: " + float);
                break;
            case 73: // I int
                number = data.readIntLE(0, data.length);
                console.log('got int: ' + number);
                break;
            case 76: // L long
                number = data.readIntLE(0, data.length);
                console.log('long: '  + number);
                break;
            case 83: // S string
                console.log('String: ' + data.toString());
                break;
            case 85: // U unsigned int
                number = data.readUIntLE(0, data.length);
                console.log('uint: ' + number);
                break;
            case 87: // W word
                number = data.readUIntLE(0, data.length);
                console.log('word: ' + number);
                break;
            case 98: // b boolean
                let bool = data.readUInt8() ? true : false;
                console.log('Boolean: ' + bool);
                break;
            case 117: // u unsigned long
                number = data.readUIntLE(0, data.length);
                console.log('ulong: ' + number);
                break;
            default:
                console.log('----------- Fallthrough ----------');
                console.log(controlbyte);
                console.log(data);
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
    // else
    // {
    //     console.log("Type")
    //     console.log(data[1])
    //     console.log("Data")
    //     data2 = data
    //     data2[0] = data[2]
    //     data2[1] = data[3]
    //     data2[2] = 0
    //     data2[3] = 0
    //     x = data2.readUInt32LE()
    //     console.log(x)
    // }
});
