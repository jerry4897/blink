//const char* host = "api.thingspeak.com";
//String url = "/update?api_key=H6YJBAB6J82QY153";   // Your Own Key here
//const char* ssid = "KT_GiGA_2G_3ED2";   // Your own ssid here
//const char* password = "fca1zg2399";  // Your own password here fca1zg2399

const char* host = "maker.ifttt.com";
String url = "/trigger/temp/with/key/d7_KiOg3TqkS18HjgZOVe";   // Your Own Key here
const int httpPort = 80;
int interval = 5000;
#include<OneWire.h>
#include<DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#define ONE_WIRE_BUS D4


const char* ssid = "AndroidHotspot4011";   // Your own ssid here
const char* password = "1234567890";  // Your own password here fca1zg2399
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
char temperatureString[6];

/*String working(String data){
  return (String("field1=")+String(data));
}*/

String working(String data){
  return (String("value1=") + String(data));
}
void delivering(String payload)
{
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpPort))
  {
    Serial.print("connection failed: ");
    Serial.println(payload);
    return;
  }

  //String getheader = "GET " + String(url) + "&" + String(payload) + " HTTP/1.1";
  String getheader = "GET " + String(url) + "?" + String(payload) + " HTTP/1.1";
  client.println(getheader);
  client.println("User-Agent: ESP8266 SukHwan Kim");
  client.println("Host: " + String(host));
  client.println("Connection: close");
  client.println();
  Serial.println(getheader);
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
  Serial.println("Done cycle.");
}
void connect_ap()
{
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\n Got WiFi, IP address: ");
  Serial.println(WiFi.localIP());
}

float getTemperature()
{
  float temp;
  do{
    DS18B20.requestTemperatures();
    temp = DS18B20.getTempCByIndex(0);
    delay(100);
  }while(temp == 85.0 || temp == (-127.0));
  return temp;
}

void setup() {
  Serial.begin(115200);
  connect_ap();
  Serial.println("ESPArduionoThingSpeak.cpp - 2018/03/07");
  DS18B20.begin();
}

void loop() {
  float temperature = getTemperature();
  dtostrf(temperature, 2, 2, temperatureString);
  Serial.println(temperatureString);
  DS18B20.requestTemperatures();
  Serial.print(DS18B20.getTempCByIndex(0));
  String payload = working(temperatureString);
  delivering(payload);
  delay(interval);
}
