#include <ESP8266WiFi.h>
#include <WiFiClient.h>
WiFiClient client;


#define RED D1
#define GREEN D2
#define BLUE D4


// Enter your WiFi setup here:
const char *SSID = "free";
const char *PASSWORD = "wifi";

//Normal connectivity test adresss
const char* host = "google.com";
const uint16_t port = 80;

//DNS-less connectivity test
const char* nodnshost = "8.8.8.8";
const uint16_t nodnsport = 53;


int NETWORKING = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

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
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  // Try forever
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    delay(1000);
    digitalWrite(BLUE, !digitalRead(BLUE));
  }
  digitalWrite(BLUE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect(host, port and client.connect(nodnshost, nodnsport))) {
    NETWORKING = 2;
  }

  if (!client.connect(host, port) and client.connect(nodnshost, nodnsport)) {
    NETWORKING = 1;
  }

  if (!client.connect(host, port) and !client.connect(nodnshost, nodnsport)) {
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
