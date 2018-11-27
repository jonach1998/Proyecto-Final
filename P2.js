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
var database = firebase.database();
var ledStatus;

$(document).ready(function(){
database.ref("pot").on("value", function(snapshot){
  console.log(snapshot.val());
  document.getElementById("titular").textContent = snapshot.val();
});

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
