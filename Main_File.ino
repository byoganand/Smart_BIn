#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>
#include<Servo.h>

#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
int sum=0;
int d,i,n,m;
Servo Servo1,Servo2;
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6
long duration;
int distance;
int distValue;
const int pin=13;

#define distCriticalLevel 15   

// protothreading
int  distReadingInterval = 10;   // interval in seconds between sensor reading (every 24h)
long distLastRead = 0;              // last time the moisture was read

long nowMillis;

const char* ssid     = "BadBoyzzz";      // wifi name
const char* password = "p@ssw0rd";      // wifi password

#define botMyChatID "1059610362"         // reference to my phone's chat
#define botToken "976862714:AAFtC1sfe4E8dW-NFRWFBWVhUhpfLqljkyo" 
#define botName "Sbin"
#define botUsername "Bin123_bot"
TelegramBOT bot(botToken, botName, botUsername);

String botCommand;
String botResponse;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // start the serial port
  Servo1.attach(2);
  Servo2.attach(4);
  Servo1.write(180);
  Servo2.write(0);
  pinMode(pin,INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.print("Connecting to \"");
  Serial.print(ssid);
  Serial.println("\"");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected (");
  Serial.print(WiFi.localIP());
  Serial.println(")");
  Serial.println("");

  // start bot
  bot.begin();
}

void loop() 
{
  long state=digitalRead(pin);
  if (state==HIGH) {
  Serial.println("Motion Detected");
  for (i=0;i<5;i++){
    float volts = (6787/(analogRead(sensor)-3));  
    int distance = (volts-4); 
    delay(100);
    sum= sum+distance; 
}
d= sum/10;
m=caldist(trigPin,echoPin);
Serial.print("Outside Distance: ");
Serial.println(d);
Serial.print("Inside Distance: ");
Serial.println(m);
if (d<7){
  n=checkdistance();
  Serial.print("Inside Distance: ");
  Serial.println(n);
  if (n < 15){
      Servo1.write(180);
    Servo2.write(0);
  }
  else {
    Servo1.write(90);
    Servo2.write(120);
  }
}
else {
  digitalWrite(trigPin,LOW);
  Servo1.write(180);
  Servo2.write(0);
}
sum=0;
delay(2000);
}
}




int checkdistance() {
  nowMillis = millis();

  if ((nowMillis > distLastRead + (distReadingInterval * 1000)) or distLastRead == 0) {
    distLastRead = nowMillis;

    distValue = caldist(trigPin,echoPin);

    if (distValue < distCriticalLevel) {
      // send value to Telegram chat
      botResponse = "Bin is Full - ";
      botResponse.concat(distValue);
      bot.sendMessage(botMyChatID, botResponse, "");    // send notification to my phone
    }

    Serial.print("Bin value: ");
    Serial.println(distValue);
    Serial.println("");
  }
  delay(1000);
  return distValue;
}






int caldist(int trigpin, int echopin){
  long dur;
  int dist;
  digitalWrite(trigpin,LOW);
  delayMicroseconds(10);

  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  dur= pulseIn(echopin,HIGH);
  dist= dur*0.034/2;
  return dist;
}
