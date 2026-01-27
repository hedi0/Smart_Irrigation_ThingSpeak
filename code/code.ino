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
