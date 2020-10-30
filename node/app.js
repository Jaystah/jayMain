const express = require('express');
const mongoose = require('mongoose');

const app = express();

const keys = require('./keys.js');
require("./models/users");

app.use(express.json());
app.use(require("./routes/auth"));

mongoose.connect(keys.MONGOURL, {
   useNewUrlParser: true,
   useUnifiedTopology: true
});

mongoose.connection.on("connected",function(){
console.log("Succesfully connected");
})

mongoose.connection.on("error",function(err){
   console.log("Error: ", err);
})

const PORT = 6969;

app.listen(PORT, ()=>{
   console.log("Server runned op ",PORT);
})