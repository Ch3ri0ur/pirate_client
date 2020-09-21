

const SerialPort = require('serialport')
const port = new SerialPort('COM4', {
    baudRate: 115200
})
const Delimiter = require('@serialport/parser-delimiter')
const parser = port.pipe(new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45]) })) 
parser.on('data', (data) => {});


