import { initializeApp } from 'firebase/app';
import { getDatabase } from 'firebase/database';
const firebase = require('firebase')
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

const fire = firebase.initializeApp(firebaseConfig);
const database = getDatabase(app);
export default database;