#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//librerias de DHT11
//Su authtiken generado por la aplicacion Blynk
char auth[]="3BJLiItzfme7HMwM6aw6qIkux2-ViKTt";
// Datos para la conexion de red wifi
char ssid[]="HUAWEI-2.4G-T2Xp";//nombre de la red WIFI
char pass[]="59EUZ5ux";//contraseña de la red WIFI

SimpleTimer timer;
int flag=0;

int Sensor = digitalRead(5);
int isButtonPressed = digitalRead(12);

void notifyOnFire()
{
  int isButtonPressed = digitalRead(16);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("fuego en la casa");
    Blynk.notify("Alert : Fuego en la casa");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}
void setup()
{
  //sensor de movimiento
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // envio correo electronico cuando el hardware se conecte al servidor de Blynk
  // parametro por defecto "correo electronico", "asunto", "mensaje a envio"
  Blynk.email("danielmqh99@gmail.com", "Subject", "My Blynk project is online.");
  pinMode(5, INPUT);//pin D1(GPI05)como entrada
  pinMode(4, OUTPUT);//pin D2(GPI04)como salida
// sensor de llama
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(16,INPUT_PULLUP);
timer.setInterval(1000L,notifyOnFire); 
}
void Alarma()
{
  // si la alarma se activa este envio un correo y espera 15 segundos.
  // varible para almacenar los estados del PIR
  if (Sensor == 0)// si el sensor detecta movimiento
  {
    Serial.println("Alarma Activada");// imprime por elmpnitor serial
    Blynk.email("danielmqh99@gmail.com", "Asunto: ", "movimiento sospechoso");
    delay(200);
  }
}
void loop()
{
  Alarma();// llama a ejecutar la funcion
  Blynk.run();
  //DHT11
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
