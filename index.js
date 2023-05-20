const express = require('express');
const PORT = process.env.PORT || 5000
var app = express();
const fire = require('./fire');
var cors = require('cors');
var bodyParser = require('body-parser');

app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.get('/', (req, res) => {
    res.send(
      '<h1>API Express & Firebase MonitoreO2</h1><ul><li><p><b>GET /ver</b></p></li><li><p><b>GET /valor</b></p></li><li><p><b>GET /estado</b></p></li><li><p><b>POST /insertar</b>  => {temp, hum, gas, ruido, nombre, fecha}</p></li><li><p><b>POST /encender</b></p></li><li><p><b>POST /apagar</b></p></li><li><p>/encender</p></li><li><p>/apagar</p></li><li><p>/estado</p></li></ul>')
  })

  app.get('/ver', (req, res) => {
    const db = fire.firestore();
      db.settings({
        timestampsInSnapshots: true
      });
      var wholeData = []
      db.collection('/BD').orderBy('Fecha', 'ID').get()
      .then(snapshot => {
        snapshot.forEach(doc => {
        
          wholeData.push(doc.data())
        });
        console.log(wholeData)
        res.send(wholeData)
      })
      .catch(error => {
        console.log('Error!', error);
    })
  })

  app.listen(PORT, () => {
    console.log(`Servidor en funcionamiento en el puerto ${PORT}`);
  });
