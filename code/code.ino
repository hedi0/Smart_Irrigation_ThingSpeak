#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define soil_pin A0
#define relay_pin D1
#define DHTPIN D4
DHT dht(DHTPIN, DHT22);

//ThingSpeak credentials
String apiKey = "THINGSPEAK_WRITE_API_KEY"; // example : 
const char* server = "api.thingspeak.com";

const char* ssid =  "PASTE_YOUR_SSID_HERE";
const char* pass =  "PASTE_YOUR_PASSWORD_HERE";

WiFiClient client;

int threshholdDRY = 800;

void setup() {
  Serial.begin(9600);

  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, HIGH);

  dht.begin();

  WiFi.begin(ssid,password);
  Serial.print("Connecting To Wifi .... ");
  while(WiFi.status() != WL_CONNECTED) {
    delay(600);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);
}

void loop(){
  int moisturevalue = analogRead(soil_pin);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan() || isnan()){
    Serial.println("Failed to read from Sensor(DHT22) ");
    return;
  }
}
