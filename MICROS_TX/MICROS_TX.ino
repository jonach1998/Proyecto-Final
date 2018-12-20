#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float lux;
  float uv;
  float temp0;
  float temp1;
  float temp2;
  float tempprom;
  float humedad;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
//Humedad
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
//Temp
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Wire.h>
//Lux
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
//UV
#include "Adafruit_SI1145.h"
//Temp
#define stemp 2
OneWire stemponewire(stemp);
DallasTemperature sensors(&stemponewire);
float promedio; 
//Lux
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
//UV
Adafruit_SI1145 uv = Adafruit_SI1145();
//BOMBA
int bomba=5;
//Humedad
#define DHTPIN            3         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Serial);

  pinMode(bomba,OUTPUT);
  digitalWrite(bomba,LOW);
  //Temp
  sensors.begin(); 
  //Lux
    if(!tsl.begin())
    {
      Serial.print("Medidor de lux no esta funcionando");
      while(1);
    }
    displaySensorDetails();
    configureSensor();
  //UV
   if (! uv.begin()) {
      Serial.println("Sensor UV no funciona");
      while (1);
    }
   //Humedad
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
        // Set delay between sensor readings based on sensor details.
    //delayMS = sensor.min_delay / 1000;
}

void loop(){
    //Temp
    sensors.requestTemperatures();
    if(sensors.getTempCByIndex(0)!= -127 and sensors.getTempCByIndex(1) != -127 and sensors.getTempCByIndex(2) != -127)
    {
    digitalWrite(bomba,LOW);
    promedio = (sensors.getTempCByIndex(0)+sensors.getTempCByIndex(1)+sensors.getTempCByIndex(2))/3;
    //Lux
    sensors_event_t event;
    tsl.getEvent(&event);
    //UV
    float UVindex = uv.readUV(); 
    UVindex = UVindex/100;
    //Humedad
    dht.humidity().getEvent(&event);
      if (isnan(event.relative_humidity)) {
      mydata.humedad=0;
      }
      else {
      mydata.humedad=(event.relative_humidity);
      }
    //Lux
      if (event.light)
      {
      mydata.lux=(event.light);
      } 
      else 
      {
      mydata.lux=0; 
      }
      mydata.uv=(UVindex);
      mydata.temp0=sensors.getTempCByIndex(0); 
      mydata.temp1=sensors.getTempCByIndex(1); 
      mydata.temp2=sensors.getTempCByIndex(2); 
      mydata.tempprom=(promedio); 
      ET.sendData();
      delay(100);
    }
      else Serial.println("Verifique sensores de temperatura");
}
//Lux
void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor); 
}

void configureSensor(void)
{
  tsl.enableAutoRange(true);      
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}
//
