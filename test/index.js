 
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const port = new SerialPort('COM3', {
    baudRate: 115200
})
// const parser = port.pipe(new Readline({ delimiter: '\r\n' }))


 
//const ByteLength = require('@serialport/parser-byte-length')
const Delimiter = require('@serialport/parser-delimiter')
//const parser = port.pipe(new ByteLength({ length: 4 }))
const parser = port.pipe(new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45]) })) 
//const parser = port.pipe(new Delimiter({ delimiter: new Uint8Array([0xff, 'P', 'i', 'r', 'A', 't','E']) })) 
parser.on('data', (buffer) => {

    let controlbyte = buffer[0];
    data = buffer.slice(1);
    switch (controlbyte) {
        case 41:
            port.write(Buffer(0x0)); //deprecation warning use the Buffer.alloc(), Buffer.allocUnsafe(), or Buffer.from() methods instead.
            break;
        case 40:
            console.log("Debug: " + data.toString());
            break;
        default:
            console.log("----------- Fallthrough ----------")
            console.log(controlbyte)
            console.log(data);
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
}
);

