var express = require('express')
var app = express()
const fs = require('fs')

app.use(express.json())
app.use(express.urlencoded({extended: true}))

app.post('/Device', (req, res) => {
    var data = req.body.data;
    var jsonData = JSON.parse(data);
    const d = new Date()
    var day = d.getDate()
    var month = d.getMonth() + 1
    var year = d.getFullYear()
    var hour = d.getHours()
    var minutes = d.getMinutes()
    var seconds = d.getSeconds()
    var dataToSave = {
        port1: jsonData.port1,
        port2: jsonData.port2,
        port3: jsonData.port3,
        waktu: {
            tanggal: year + "/" + month + "/" + day,
            jam: hour + ":" + minutes + ":" + seconds
        }
    }
    var jsonDatabase = getDataSensor()
    jsonDatabase.push(dataToSave)
    saveDataSensor(jsonDatabase)
    var relay = getRelay()
    res.json(relay[relay.length - 1])
})

app.post('/Relay', (req, res) => {
    const d = new Date()
    var day = d.getDate()
    var month = d.getMonth() + 1
    var year = d.getFullYear()
    var hour = d.getHours()
    var minutes = d.getMinutes()
    var seconds = d.getSeconds()
    var data = {
        port1: req.body.port1,
        port2: req.body.port2,
        port3: req.body.port3,
        waktu: {
            tanggal: year + "/" + month + "/" + day,
            jam: hour + ":" + minutes + ":" + seconds
        }
    }
    var relay = getRelay()
    relay.push(data)
    saveRelay(relay)
    res.json({
        status: true,
        msg: "succes update relay"
    })
})

app.get('/Sensor', (req, res) => {
    var data = getDataSensor()
    res.json(data[data.length - 1])
})

app.get('/Port', (req, res) => {
    var data = getRelay()
    res.json(data[data.length - 1])
})

app.post('/test', (req, res) => {
    var rec = req.body.data;
    var data = JSON.parse(rec)
    console.log(data)
    console.log(data[0])
})

app.listen(8080)

function getDataSensor() {
    return JSON.parse(fs.readFileSync('sensor.json'))
}

function saveDataSensor(data) {
    fs.writeFileSync('sensor.json', JSON.stringify(data))
}

function getRelay() {
    return JSON.parse(fs.readFileSync('relay.json'))
}

function saveRelay(data) {
    fs.writeFileSync('relay.json', JSON.stringify(data))
}



