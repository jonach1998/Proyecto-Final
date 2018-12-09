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

void setup() {
Serial.begin(9600);
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
}

void loop() {
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
    
    //Lux
      if (event.light)
      {
      Serial.print(event.light); 
      Serial.print(" lux    "); 
      } 
      else 
      {
      Serial.print(0); 
      Serial.print(" lux    "); 
      }
      Serial.print(sensors.getTempCByIndex(0)); 
      Serial.print(" grados0    ");
      Serial.print(sensors.getTempCByIndex(1)); 
      Serial.print(" grados1    ");
      Serial.print(sensors.getTempCByIndex(2)); 
      Serial.print(" grados2    ");
      Serial.print("Promedio: "); 
      Serial.print(promedio); 
      Serial.print(" grados    ");
      Serial.print("UV: ");
      Serial.println(UVindex);
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
