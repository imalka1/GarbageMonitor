#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "HX711.h"

const char* ssid = "iDialog 4G - 2";
const char* password = "149homewifidialog";
//const char* ssid = "TP-Link_AP_7E94";
//const char* password = "tplink1234321";

const char* label = "A2";
//float weight = 50.5;
float weight = 32;
//float weight = 41;
//float weight = 78;
//float weight = 46;

boolean isZero = false;
//HX711 scale;
WiFiServer server(80);

void setup() {
  Serial.begin(9600); //Serial connection
  WiFi.begin(ssid, password);   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(D0, LOW);
  server.begin();
  Serial.println("Wifi OK");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

//  scale.begin(D6, D7);
//  scale.set_scale(-7050); //This value is obtained by using the SparkFun_HX711_Calibration sketch
//  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  setToInitial();
}

void loop() {
  //    server.handleClient();
  Serial.println(digitalRead(D2));

  if (digitalRead(D2) == 1 && !isZero) {
    isZero = true;
    weight = 0;
    sendRequest("http://192.168.1.4:8080/api/place/binSignal/" + String(label) + "/" + String(weight));
  }

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {}
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request
  if (request.indexOf("/get_weight") != -1)  {
    digitalWrite(LED_BUILTIN, LOW);
//    weight = scale.get_units();
    sendRequest("http://192.168.1.4:8080/api/place/binSignal/" + String(label) + "/" + String(weight));
    digitalWrite(LED_BUILTIN, HIGH);
    setToInitial();
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("OK");

}

void setToInitial() {
  isZero = false;
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  pinMode(D2, INPUT);

}

void sendRequest(String url) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient
    http.begin(url); //Specify request destination
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
    }
    http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");
  }
}
