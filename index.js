const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const server = require("http").createServer();
const io = require("socket.io")(server);
const port = new SerialPort('/dev/ttyACM0', {
    baudRate: 115200
})
const parser = port.pipe(new Readline({ delimiter: '\r\n' }))


io.on("connection", (socket) => {
    console.log("connected to: " + socket.client.id)
    // socket.on("event", (data) => {
    //     console.log(data);
    // });
    parser.on('data', (data) => {
        if (data.startsWith("I")) {
            console.log(data)
            return
        }
	// console.log(data)
        socket.emit("measurements", Date.now() + "," + data)
    });
    socket.on("disconnect", () => {
        console.log("disconnected");
        socket.removeAllListeners();
        parser.removeAllListeners();
        // socket.disconnect(close = true)

    });
    socket.on("settings", (data) => {
        port.write(data.join(",") + "T")
        console.log(data)
    })
});
server.listen(3000, "0.0.0.0");
