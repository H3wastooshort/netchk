#include <ESP8266WiFi.h>
#include <WiFiClient.h>
WiFiClient client;


#define RED D1
#define GREEN D2
#define BLUE D4


// Enter your WiFi setup here:
const char *SSID = "vERY SeCURe";
const char *PASSWORD = "12345678";

const char* host = "google.com";
const uint16_t port = 80;

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
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);
    delay(1000);
    digitalWrite(BLUE, !digitalRead(BLUE));
  }
  digitalWrite(BLUE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect(host, port)) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    delay(50);
    digitalWrite(BLUE, LOW);
  }

  if (!client.connect(host, port)) {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, HIGH);
    delay(50);
    digitalWrite(BLUE, LOW);
  }
  client.stop();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);
    delay(1000);
    digitalWrite(BLUE, !digitalRead(BLUE));
  }
  digitalWrite(BLUE, LOW);
}
