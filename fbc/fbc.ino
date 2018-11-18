#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define red "Fer"
#define password "crustaceo"
#define FIREBASE_HOST "prueba1-a570f.firebaseio.com"
#define FIREBASE_AUTH "S4rm9wc2qH6SEI997K9cG3OccNN5ETFgkbsagcwK"
int analog= A0;
byte control;
byte led=5;
void setup ()
{
  Serial.begin (9600);
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
  pinMode(led,OUTPUT);
}
void loop ()
{   
    spren();
    int x= analogRead(analog);
    Firebase.setInt("a",x);
    Serial.println(x);
  
}
void spren()
{
  control=Firebase.getInt("controlb");
    if(control==1)
    {digitalWrite(led,HIGH);}
    else
  {digitalWrite(led,LOW);}
  Serial.println(control);

}
