// Import the functions you need from the SDKs you need
const { initializeApp } = require ("firebase/app");


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
const fire = initializeApp(firebaseConfig);
module.exports = fire;