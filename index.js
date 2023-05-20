const express = require('express');
const PORT = process.env.PORT || 5000
var app = express();
const fire = require('./fire');
const database = fire.database();
var cors = require('cors');
var bodyParser = require('body-parser');

app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

  
  app.listen(PORT, () => {
    console.log(`Servidor en funcionamiento en el puerto ${PORT}`);
  });
