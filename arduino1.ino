#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial // comment this out to disable prints and save space
#include <SPI.h> 
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
//you should get Auth Token in The Blynk App.
//go to the Project Settings (nut icon).
char auth[] = "3BJLiItzfme7HMwM6aw6qIkux2-ViKTt";
char ssid[] = "HUAWEI-2.4G-T2Xp";
char pass[] = "59EUZ5ux";
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

int mq2 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan (t)){
    Serial.println("Failed to read from DHT sendor!");  
    return;
  }
  // you can send any value at any time.
  // please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  //Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}
void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
void getSendData()
{
data = analogRead(mq2); 
  Blynk.virtualWrite(V2, data);
 
  if (data > 700 )
  {
    Blynk.notify("Smoke Detected!"); 
  }
 
}
