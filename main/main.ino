#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// O IP padrão é o 192.168.4.1
const char* ssid = "KickBall"; // Nome da rede Wi-Fi do Access Point
const char* password = "KB102030"; // Senha para o Access Point

// Declaração VAR
const int ledPin = 2; // Led do ESP8266
bool ledState = false; // Estado atual do LED

const int INP1 = 5;
const int INP2 = 6;

ESP8266WebServer server(80);

const char* html = R"html(
<html> 
  <head>   
    <title>KickBall</title> 
    <style>
      #title {
        display: flex;
        justify-content: center;
        align-items: center;
        font-size: 30px;
      }

      .joystick {
        display: flex;
        align-items: center;
        justify-content: center;
        padding-top: 130px;
      }

      .button-lr {
        background-color: yellow;
        font-size: 20px;
        width: 200px;
        height: 200px;
        margin-right: 50px;
        padding: 50px;
        padding-left: 10px;
        padding-right: 10px;
        border-radius: 50%;
        
      }

      #button-hit{
        background-color: red;
        font-size: 20px;
        width: 200px;
        height: 200px;
        margin-right: 50px;
        padding: 50px;
        margin-left: 70px;
        padding-left: 10px;
        padding-right: 10px;
        border-radius: 50%;
      }
    @media (max-width: 500px){
      #title {
        display: flex;
        justify-content: center;
        align-items: center;
        font-size: 30px;
      }

      .joystick {
        display: flex;
        align-items: center;
        justify-content: center;
        padding-top: 130px;
      }

      .button-lr {
        background-color: yellow;
        font-size: 20px;
        width: 200px;
        height: 200px;
        margin-right: 50px;
        padding: 50px;
        padding-left: 10px;
        padding-right: 10px;
        border-radius: 50%;
        
      }

      #button-hit{
        background-color: red;
        font-size: 20px;
        width: 200px;
        height: 200px;
        margin-right: 50px;
        padding: 50px;
        margin-left: 70px;
        padding-left: 10px;
        padding-right: 10px;
        border-radius: 50%;
      }
    }
    </style>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>  
   </head>  
   <body> 

    <header>
      <div>
        <h1 id="title">Kick Ball Game</h1>
      </div>
    </header>
    
    <div class="joystick">
      <a href="http://192.168.4.1/on">
        <button class="button-lr">Direita</button>
      </a>
      <a href="http://192.168.4.1/off">
        <button class="button-lr">Esquerda</button>
      </a>
      <a href="#">
        <button id="button-hit">Chute</button>
      </a>
    </div>

    </body>  
</html>
)html";

void handleRoot() {
  server.send(200, "text/html", html);
}

void handleOn() {
  ledState = true;
  // Pin 0: 
  digitalWrite(INP1, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  ledState = false;
  // Pin: 2
  digitalWrite(INP2, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  pinMode(INP1, OUTPUT);
  digitalWrite(INP1, LOW);

  pinMode(INP2, OUTPUT);
  digitalWrite(INP2, LOW);

  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}