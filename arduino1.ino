#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial 
#include <SPI.h> 
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>


String apiKey = "TBMU0NE6N4E3IHBK"; 
char auth[] = "3BJLiItzfme7HMwM6aw6qIkux2-ViKTt";
char ssid[] = "HUAWEI-2.4G-T2Xp";
char pass[] = "59EUZ5ux";
const char* server = "api.thingspeak.com";
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

SimpleTimer timer;

int mq2 = A0; 
int data = 0;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan (t)){
    Serial.println("Failed to read from DHT sendor!");  
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
void setup()
{
  Serial.begin(9600);
  delay(10);
  dht.begin();
 
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(1000L, sendSensor);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}
void loop()
{
  Blynk.run(); 
  timer.run(); 

float u = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(u) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(u);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperatura: ");
                             Serial.println(t);
                             Serial.print("Humedad: ");
                             Serial.println(u);
                             Serial.println("%. Enviar a Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Esperando...");
  

  delay(1000);


  float h = analogRead(A0);
if (isnan(h))
{
Serial.println("Falta el sensor de GAS");
return;
}
 

{
String postStr = apiKey;
postStr += "&amp;field1=";
postStr += String(h/1023*100);
postStr += "r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
Serial.print("Gas Nivel: ");
Serial.println(h/1023*100);
Serial.println("Datos enviados a Thingspeak");
}
delay(500);
client.stop();
Serial.println("cargando...");
 

delay(1500);

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
