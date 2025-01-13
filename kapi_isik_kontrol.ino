#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "wi-fi_name";
const char* password = "wi-fi_password";

ESP8266WebServer server(80); // Web server oluşturuluyor
Servo myServo;               // Servo motor nesnesi oluşturuluyor
int servoPin = D1;           // Servo motorun bağlı olduğu pin
int ledPin = D4;             // LED'in bağlı olduğu pin

// Kapıyı açma fonksiyonu
void openDoor() {
  myServo.write(90);         // Servo motoru 90°'a hareket ettir (kapı açık)
  String veri = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ClassHub</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        text-align: center;
        background-color: #f4f4f4;
        margin: 0;
        padding: 20px;
      }
      h1 {
        color: #333;
      }
      button {
        padding: 10px 20px;
        margin: 10px;
        font-size: 16px;
        color: white;
        background-color: #007bff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      button:hover {
        background-color: #0056b3;
      }
    </style>
  </head>
  <body>
    <h1>ClassHub 4.0</h1>
    <p>Kapi Acildi!</p>
    <button onclick="location.href='/ac'">Kapiyi Ac</button>
    <button onclick="location.href='/kapat'">Kapiyi Kapat</button>
    <button onclick="location.href='/ledac'">LED Ac</button>
    <button onclick="location.href='/ledkapat'">LED Kapat</button>
    <button onclick="location.href='/'">Yenile</button>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", veri);
}

// Kapıyı kapama fonksiyonu
void closeDoor() {
  myServo.write(0);          // Servo motoru 0°'a hareket ettir (kapı kapalı)
  String veri = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ClassHub</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        text-align: center;
        background-color: #f4f4f4;
        margin: 0;
        padding: 20px;
      }
      h1 {
        color: #333;
      }
      button {
        padding: 10px 20px;
        margin: 10px;
        font-size: 16px;
        color: white;
        background-color: #007bff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      button:hover {
        background-color: #0056b3;
      }
    </style>
  </head>
  <body>
    <h1>ClassHub 4.0</h1>
    <p>Kapi Kapandi!</p>
    <button onclick="location.href='/ac'">Kapiyi Ac</button>
    <button onclick="location.href='/kapat'">Kapiyi Kapat</button>
    <button onclick="location.href='/ledac'">LED Ac</button>
    <button onclick="location.href='/ledkapat'">LED Kapat</button>
    <button onclick="location.href='/'">Yenile</button>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", veri);
}

// LED'i açma fonksiyonu
void ledOn() {
  digitalWrite(ledPin, HIGH); // LED'i yak
  String veri = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ClassHub</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        text-align: center;
        background-color: #f4f4f4;
        margin: 0;
        padding: 20px;
      }
      h1 {
        color: #333;
      }
      button {
        padding: 10px 20px;
        margin: 10px;
        font-size: 16px;
        color: white;
        background-color: #007bff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      button:hover {
        background-color: #0056b3;
      }      
    </style>
  </head>
  <body>
    <h1>ClassHub 4.0</h1>
    <p>LED Acildi!</p>
    <button onclick="location.href='/ac'">Kapiyi Ac</button>
    <button onclick="location.href='/kapat'">Kapiyi Kapat</button>
    <button onclick="location.href='/ledac'">LED Ac</button>
    <button onclick="location.href='/ledkapat'">LED Kapat</button>
    <button onclick="location.href='/'">Yenile</button>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", veri);
}

// LED'i kapama fonksiyonu
void ledOff() {
  digitalWrite(ledPin, LOW); // LED'i söndür
  String veri = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ClassHub</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        text-align: center;
        background-color: #f4f4f4;
        margin: 0;
        padding: 20px;
      }
      h1 {
        color: #333;
      }
      button {
        padding: 10px 20px;
        margin: 10px;
        font-size: 16px;
        color: white;
        background-color: #007bff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      button:hover {
        background-color: #0056b3;
      }
    </style>
  </head>
  <body>
    <h1>ClassHub 4.0</h1>
    <p>LED Kapandi!</p>
    <button onclick="location.href='/ac'">Kapiyi Ac</button>
    <button onclick="location.href='/kapat'">Kapiyi Kapat</button>    
    <button onclick="location.href='/ledac'">LED Ac</button>
    <button onclick="location.href='/ledkapat'">LED Kapat</button>
    <button onclick="location.href='/'">Yenile</button>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", veri);
}

// Ana sayfa
void refreshPage() {
  String veri = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ClassHub</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        text-align: center;
        background-color: #f4f4f4;
        margin: 0;
        padding: 20px;
      }
      h1 {
        color: #333;
      }
      button {
        padding: 10px 20px;
        margin: 10px;
        font-size: 16px;
        color: white;
        background-color: #007bff;
        border: none;
        border-radius: 5px;
        cursor: pointer;
      }
      button:hover {
        background-color: #0056b3;
      }
    </style>
  </head>
  <body>
    <h1>ClassHub 4.0</h1>
    <p>Kapinin durumunu ve LED'i kontrol edin:</p>
    <button onclick="location.href='/ac'">Kapiyi Ac</button>
    <button onclick="location.href='/kapat'">Kapiyi Kapat</button>
    <button onclick="location.href='/ledac'">LED Ac</button>
    <button onclick="location.href='/ledkapat'">LED Kapat</button>
    <button onclick="location.href='/'">Yenile</button>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", veri);
}

void setup() {
  myServo.attach(servoPin);  // Servo motoru belirtilen pine bağla
  myServo.write(0);          // Başlangıçta kapı kapalı
  pinMode(ledPin, OUTPUT);   // LED pinini çıkış olarak ayarla
  digitalWrite(ledPin, LOW); // Başlangıçta LED kapalı
  Serial.begin(9600);        // Seri haberleşmeyi başlat 115200
  WiFi.begin(ssid, password);// WiFi ağına bağlan

  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi'ye bağlanıldı: ");
  Serial.println(ssid);
  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());

  // URL eşlemeleri
  server.on("/ac", openDoor);
  server.on("/kapat", closeDoor);
  server.on("/ledac", ledOn);
  server.on("/ledkapat", ledOff);
  server.on("/", refreshPage);

  server.begin();
  Serial.println("HTTP server başlatıldı");
}

void loop() {
  server.handleClient(); // İstemcilerden gelen istekleri işle
}
