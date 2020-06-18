const express = require("express");
// const bodyParser = require("body-parser");
const cors = require("cors");
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
// const stream = require("./routes/stream");
// const getData = require("./services/datasource");
const port = new SerialPort('/dev/ttyACM0', {
    baudRate: 115200
})
const parser = port.pipe(new Readline({ delimiter: '\r\n' }))
const app = express();

app.use(express.json());


// $(1char for id)(1char for datatype)((+-)Digitamount of chars)E((+-)Expamount of chars)#%

// $(1char for id)(1char for datatype)((+-)Digitamount of chars)E((+-)Expamount of chars)#(1id)(1datatype)((+-)Digitamount of chars)E((+-)Expamount of chars)#%

// app.use("/stream", stream);
app.get("/stream", (req, res) => {

    res.set({
        "Content-Type": "text/event-stream",
        "Cache-Control": "no-cache",
        Connection: "keep-alive",

        // enabling CORS
        'Access-Control-Allow-Origin': "*",
        'Access-Control-Allow-Headers': 'Origin, X-Requested-With, Content-Type, Accept'
    });


    parser.on('data', (data) => {
        if (data.startsWith('I')) {
            console.log(data);
            return;
        }
        console.log(JSON.stringify(Date.now() + "," + data))
        //   socket.emit("measurements", Date.now() + "," + data)
        res.write(`event: message\n`);
        res.write(`data: "${Date.now() + "," + data}"\n\n`)
        // res.write(Date.now() + "," + data + "\n\n")
    });

    //   setInterval(() => {
    //     res.write(`event: message\n`);
    //     res.write(`data: ${JSON.stringify(getData())}\n\n`);
    //   }, 2000)

});

app.use(cors());
// app.use(bodyParser.json());
// app.use(bodyParser.urlencoded({ extended: false }));

const PORT = 3000;

app.listen(PORT, () => console.log(`The server is listening on port ${PORT}`));
