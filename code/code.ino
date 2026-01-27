#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define soil_pin A0
#define relay_pin D1
#define DHTPIN D4

#define soilDRY 310
#define soilWET 750

//ThingSpeak credentials
const char* WriteAPIkey = "THINGSPEAK_WRITE_API_KEY"; // example : CVC8CV4VC8L4VCVC
unsigned long ChannelID = PASTE_YOUR_CHANNEL_ID_HERE; // example : 4848484

const char* ssid =  "PASTE_YOUR_SSID_HERE";
const char* pass =  "PASTE_YOUR_PASSWORD_HERE";

WiFiClient client;
DHT dht(DHTPIN, DHT22);

void setup() {
  Serial.begin(9600);

  pinMode(relay_pin, OUTPUT);
  // we need it OFF at the start
  digitalWrite(relay_pin, HIGH); //most relay modules are "active-LOW"

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
  int soilmoistureValue = analogRead(soil_pin);
  // change the analog read value from number to percentage 
  int moistpercentage = map(soilmoistureValue,soilDRY,soilWET,0,100);
  moistpercentage = constrain(moistpercentage,0,100);
  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan() || isnan()){
    Serial.println("Failed to read from Sensor(DHT22) ");
    return;
  }

  if(moistpercentage < 40){
    digitalWrite(relay_pin, LOW);
    Serial.println("Pump turned ON (Active)");
  }else{
    digitalWrite(relay_pin, HIGH);
    Serial.println("Pump turned OFF");
  }
  ThingSpeak.setField(1,moistpercentage);
  ThingSpeak.setField(2,temperature);
  ThingSpeak.setField(3,humidity);
  ThingSpeak.writeFields(ChannelID,WriteAPIkey);

  delay(15000);
}
