#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <EasyTransfer.h>
#include <SoftwareSerial.h>
#define red "Fer"
#define password "crustaceo"
#define FIREBASE_HOST "pv12-3bba3.firebaseio.com"
#define FIREBASE_AUTH "KPMkDtjaA54Aiz0mNbRQPv3sikpTxjLK75BV9lui"
EasyTransfer ET; 

SoftwareSerial myserial(4, SW_SERIAL_UNUSED_PIN); 

struct RECEIVE_DATA_STRUCTURE{

  float lux;
  float uv;
  float temp0;
  float temp1;
  float temp2;
  float tempprom;
};


RECEIVE_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  myserial.begin(9600);
  ET.begin(details(mydata), &myserial);
  WiFi.begin(red, password);
  Serial.print("Conectando");
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Si conecto ");
  Serial.print(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  if(ET.receiveData()){
    digitalWrite(LED_BUILTIN,LOW);
    Serial.print("Lux: "); 
    Serial.println(mydata.lux);
    Serial.print("UV: ");
    Serial.println(mydata.uv);
    Serial.print("temp0: ");
    Serial.println(mydata.temp0);
    Serial.print("temp1: ");
    Serial.println(mydata.temp1);
    Serial.print("temp2: ");
    Serial.println(mydata.temp2);
    Serial.print("tempprom: ");
    Serial.println(mydata.tempprom);
    Firebase.setFloat("lux",mydata.lux);
    Firebase.setFloat("uv",mydata.uv);
    Firebase.setFloat("temp0",mydata.temp0);
    Firebase.setFloat("temp1",mydata.temp1);
    Firebase.setFloat("temp2",mydata.temp2);
    Firebase.setFloat("temprom",mydata.tempprom);
    delay(50);
  }
  digitalWrite(LED_BUILTIN,HIGH);
  delay(50);
}
