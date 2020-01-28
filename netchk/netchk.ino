#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266Ping.h> //https://github.com/dancol90/ESP8266Ping
#include <EEPROM.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
WiFiClient client;
WiFiManager wifiManager;

#define RED D1
#define GREEN D2
#define BLUE D4

//Normal connectivity test adresss
const char* host = "google.com";
const uint16_t port = 80;

//DNS-less connectivity test
IPAddress nodnshost (8, 8, 8, 8);

int NETWORKING = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(D6, INPUT_PULLUP);

  Serial.begin(115200);

  digitalWrite(RED, HIGH);
  delay(100);
  digitalWrite(RED, LOW);
  delay(100);
  digitalWrite(GREEN, HIGH);
  delay(100);
  digitalWrite(GREEN, LOW);
  delay(100);
  digitalWrite(BLUE, HIGH);
  delay(100);
  digitalWrite(BLUE, LOW);
  delay(100);
  wifiManager.autoConnect();
  digitalWrite(BLUE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect(host, port) and Ping.ping(nodnshost)) {
    NETWORKING = 2;
  }

  if (!client.connect(host, port) and Ping.ping(nodnshost)) {
    NETWORKING = 1;
  }
  
    if (client.connect(host, port) and !Ping.ping(nodnshost)) {
    NETWORKING = 1;
  }

  if (!client.connect(host, port) and !Ping.ping(nodnshost)) {
    NETWORKING = 0;
  }

  ledUpdate();

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    delay(1000);
    digitalWrite(BLUE, !digitalRead(BLUE));
  }
  digitalWrite(BLUE, LOW);
}


void ledUpdate() {
  switch (NETWORKING) {
    case 0:
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      delay(50);
      digitalWrite(BLUE, LOW);
      client.stop();
      break;
    case 1:
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      delay(50);
      digitalWrite(BLUE, LOW);
      client.stop();
      break;
    case 2:
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, HIGH);
      delay(50);
      digitalWrite(BLUE, LOW);
      client.stop();
      break;
  }
}
