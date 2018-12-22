// Initialize Firebase
var config = {
apiKey: "AIzaSyBgQObWhwfL_itEGne-nNHfbbEcyaG4Ih4",
authDomain: "pv12-3bba3.firebaseapp.com",
databaseURL: "https://pv12-3bba3.firebaseio.com",
projectId: "pv12-3bba3",
storageBucket: "pv12-3bba3.appspot.com",
messagingSenderId: "396217654403"
};

firebase.initializeApp(config);
$(document).ready(function(){
var database = firebase.database();



//Recolecion de Datos de los sensores

database.ref("hr").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("s1h").textContent = snapshot.val();
});

database.ref("temprom").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("s2t").textContent = snapshot.val();
});


database.ref("lux").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("s3l").textContent = snapshot.val();
});

database.ref("uv").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("s4u").textContent = snapshot.val();
});


database.ref("temp0").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("st0").textContent = snapshot.val();
});

database.ref("temp1").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("st1").textContent = snapshot.val();
});


database.ref("temp2").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("st2").textContent = snapshot.val();
});
//Recoleccion de datos de los sensores

function sliderChange (val){

document.getElementById('id');



}


$(".lightButton").click(function(){
  var firebaseRef = firebase.database().ref().child("led");
  if(ledStatus == 1){
    firebaseRef.set(0);
    ledStatus = 0;
  } else {
    firebaseRef.set(1);
    ledStatus = 1;
  }});
  });
