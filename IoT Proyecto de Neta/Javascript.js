  var config = {
    apiKey: "AIzaSyA73TumoMqGZhmWVQEr3bP_WpBpaj0YD3M",
    authDomain: "ejemplo-4ae78.firebaseapp.com",
    databaseURL: "https://ejemplo-4ae78.firebaseio.com",
    projectId: "ejemplo-4ae78",
    storageBucket: "ejemplo-4ae78.appspot.com",
    messagingSenderId: "364795928404"
  };
  firebase.initializeApp(config);
  var correo = document.getElementById("correo");
  var password = document.getElementById("password");
  const auth = firebase.auth();
function signIn(){

  var correo_t= document.getElementById("correo").value;
  var password_t = document.getElementById("password").value;

  auth.signInWithEmailAndPassword(correo_t,password_t).catch(function(error0){
   var errorCode = error.code;
    var errorMessage = error.message;
    console.log(errorMessage);
  });
}
  function prender(){
      firebase.database().ref("Aspersor").set(1);
  }
  function apagar(){
      firebase.database().ref("Aspersor").set(0);
  }

auth.onAuthStateChanged(function(user){

  if(user){
    document.getElementById("apagar").classList.remove("invisible");
    document.getElementById("prender").classList.remove("invisible");
    document.getElementById("container").classList.remove("invisible");
    var luz = firebase.database().ref().child("Luz");
    var hum = firebase.database().ref().child("Humedad");
    var temp = firebase.database().ref().child("Temperatura");
    var red = firebase.database().ref().child("RojoOn");
    var green = firebase.database().ref().child("Viento");
    var intruso = firebase.database().ref().child("Intruso");
    var intruso = firebase.database().ref().child("Intruso");
    var aspersor = firebase.database().ref().child("Aspersor");

    luz.on('value', function(datasnapshot){
  document.getElementById("text").innerText = datasnapshot.val();
  });

hum.on('value', function(datasnapshot){
  document.getElementById("text1").innerText = datasnapshot.val();
  });

temp.on('value', function(datasnapshot){
  document.getElementById("text2").innerText = datasnapshot.val();
  });

red.on('value', function(datasnapshot){
  var rojo = datasnapshot.val();
  console.log(rojo);
  if(rojo==1){
    document.getElementById("rojin").innerText= "Prendido";
  }else{
    document.getElementById("rojin").innerText= "Apagado";
  }
  });

green.on('value', function(datasnapshot){
  var verde = datasnapshot.val();
   if(verde==1){
    document.getElementById("verdin").innerText= "No hay mucho viento";
  }else{
    document.getElementById("verdin").innerText= "Hay mucho viento";
  }
  });

intruso.on('value', function(datasnapshot){
  var intru = datasnapshot.val();
   if(intru==1){
    document.getElementById("seguridah").innerText= "Intruso Detectado";
  }else{
    document.getElementById("seguridah").innerText= "Seguro";
  }
  });
aspersor.on('value', function(datasnapshot){
  var aspe = datasnapshot.val();
   if(aspe==1){
    document.getElementById("aspersoh").innerText= "Prendido";
  }else{
    document.getElementById("aspersoh").innerText= "Apagado";
  }
  });

  } else{
      document.getElementById("apagar").className+= "invisible";
      document.getElementById("prender").className+= "invisible";
      document.getElementById("container").className+= "invisible";

  }
});