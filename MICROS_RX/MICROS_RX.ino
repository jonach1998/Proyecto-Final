#include <EasyTransfer.h>
#include <SoftwareSerial.h>
//create object
EasyTransfer ET; 

SoftwareSerial myserial(4, SW_SERIAL_UNUSED_PIN); // RX, TX

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float lux;
  float uv;
  float temp0;
  float temp1;
  float temp2;
  float tempprom;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(9600);
  myserial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &myserial);
}

void loop(){
  //check and see if a data packet has come in. 
  if(ET.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out.
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
  }
  //you should make this delay shorter then your transmit delay or else messages could be lost
  delay(250);
}
