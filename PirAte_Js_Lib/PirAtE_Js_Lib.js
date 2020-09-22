

// const SerialPort = require('serialport')
// const port = new SerialPort('COM4', {
//     baudRate: 115200
// })
// const delimiter = require('@serialport/parser-delimiter')
// const parser = port.pipe(new Delimiter({ delimiter: new Uint8Array([0xff, 0x50, 0x69, 0x72, 0x41, 0x74, 0x45]) })) 
// parser.on('data', (data) => {});


//SendtoArdu buffer Map by index
//SendtoWeb buffer Map by index
//Debug handling
//Zyklisches weiterreichen 
//parser Ardu Msg zu Json {key index} {data:type} 
//parser Json zu Ardu Msg xxPirAtE
//Parser for all supported data type

// const arduino_buffer = {

// }

// let arduino_buffer = {}; 
// arduino_buffer["test"] = 23
// console.log(arduino_buffer);
// let andere_variable = arduino_buffer["test"]
// console.log(andere_variable);
// delete arduino_buffer["test"]
// console.log(arduino_buffer);
// arduino_buffer[1] = {timestamp: "12uhr" , value: 14}
// console.log(arduino_buffer);

// const testvar = "test"
// arduino_buffer = {}; 
// arduino_buffer.testvar = 23
// console.log(arduino_buffer);
// andere_variable = arduino_buffer.testvar
// console.log(andere_variable);
// delete arduino_buffer.testvar
// console.log(arduino_buffer);
// arduino_buffer[1] = {timestamp: "12uhr" , value: 14}
// console.log(arduino_buffer);


const ardu_map = new Map();
var i;
for (i = 0; i < 10; i++) {
  ardu_map.set(i, {timestamp: Date.now(), datatype: "int", value: i*2})
}
console.log(JSON.stringify([...ardu_map]));
ardu_map.set("3", {timestamp: "jetzt", value: 12.4, datatype: "float"})
console.log(ardu_map);
ardu_map.set("3", {timestamp: "jetzt", value: 99.9, datatype: "float"})
console.log(ardu_map);
let varyvar = ardu_map.get("5");
console.log(varyvar);
ardu_map.delete("3")
console.log(ardu_map);
ardu_map.forEach((value, key) => console.log(key + " : " + value.value))
console.log(ardu_map);
// test = "öljes4hertjfsdf"
// const thing = {}
// thing[1513] = { timestamp: Date.now(), datatype: "int", value: 5134 * 2 }
// for (i = 0; i < 10; i++) {
//     thing[test[i]] = { timestamp: Date.now(), datatype: "int", value: i * 2 }
// }
// delete thing[3]
// thing[3] = { timestamp: Date.now(), datatype: "int", value: 4 * 2 }
// console.log(JSON.stringify(thing))
// Object.keys(thing).forEach(key => {
//     console.log(key + " : " + thing[key].value);
//     delete thing[key]
// })

// console.log(thing)


// https://www.samanthaming.com/tidbits/37-dynamic-property-name-with-es6/





