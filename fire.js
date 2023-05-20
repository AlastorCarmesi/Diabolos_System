const firebase = require('firebase/app');
const { initializeApp } = require('firebase/app')
const { getDatabase } = require('firebase/database');
require('firebase/database');
require("firebase/firestore");

const firebaseConfig = {
  apiKey: "AIzaSyDiLnrTW9q6cCqFektC-HpxQw65Y3ZCVQ8",
  authDomain: "diabolos-security-system.firebaseapp.com",
  databaseURL: "https://diabolos-security-system-default-rtdb.firebaseio.com",
  projectId: "diabolos-security-system",
  storageBucket: "diabolos-security-system.appspot.com",
  messagingSenderId: "828860406671",
  appId: "1:828860406671:web:754021ad65f1fec99e89fa",
  measurementId: "G-BTPB0XBY5B"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
// Obtener la instancia de la base de datos
const fire = getDatabase(app);
// Obtener una instancia de Firestore
const Firestore = firebase.firestore();
module.exports ={
    fire,
    Firestore
};