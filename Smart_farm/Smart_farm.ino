#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
const char *ssid =  "";      // Enter your WiFi Name
const char *pass =  "";     // Enter your WiFi Password
#define DHTPIN D3          // GPIO Pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);
WiFiClient client;

const int moisturePin = A0;             // moisteure sensor pin
const int motorPin = D0;
unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;
float moisturePercentage;              //moisture reading
float h;                // humidity reading
float t;               //temperature reading
float a;              //pollution reading
void setup()
{
  Serial.begin(115200);
  delay(1000);
  pinMode(motorPin, OUTPUT);
  pinMode(moisturePin, INPUT);

  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
float a = analogRead(D1);
if (isnan(a))
{
Serial.println("Failed to read from MQ-5 sensor!");
return;
}

{
  unsigned long currentMillis = millis(); // grab current time

  h = dht.readHumidity();     // read humiduty
  t = dht.readTemperature();     // read temperature

  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );

  
    Serial.print("Soil Moisture is  = ");
    Serial.print(moisturePercentage);
    Serial.println("%");
    
  

if (moisturePercentage < 50) {
  Serial.print("motor on");
  digitalWrite(motorPin, HIGH);         // turn on motor
}
else {
  Serial.print("motor off");
  digitalWrite(motorPin, LOW);          // turn off mottor
}
  if (WiFi.status() == WL_CONNECTED) {  //Check WiFi connection status
    HTTPClient http;                    //Declare an object of class HTTPClient
    String url = "\\your website file folder URL\\temp=" + String(t) + "&hum=" + String(h) + "&moisture=" + String(a) + "&air=" + String(moisturePercentage);
    Serial.println(url);
    http.begin(client, url);          //Specify request destination
    int httpCode = http.GET();            //Send the request
    if (httpCode > 0) {                   //Check the returning code
      String payload = http.getString();  //Get the request response payload
      Serial.println(payload);            //Print the response payload
    }
    http.end();  //Close connection
  }
}
