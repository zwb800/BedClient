/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
//ADC_MODE(ADC_VCC);

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "头部码头"
#define STAPSK  "19832336162"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.2.138";
const uint16_t port = 8080;


ESP8266WiFiMulti WiFiMulti;
WiFiUDP Udp;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  // We start by connecting to a WiFi network
  WiFi.hostname("Bed1");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);

}

// the loop function runs over and over again forever
void loop() {
 digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)


  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  Udp.beginPacket(host, port);
  Udp.write(sensorValue >> 8);
  Udp.write(sensorValue & 0xFF );
  Udp.endPacket();
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  delay(900);                       // wait for a second
}
