const express = require('express');
const PORT = process.env.PORT || 5000
var app = express();
var fire = require('./fire');
var cors = require('cors');
var bodyParser = require('body-parser');

app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));