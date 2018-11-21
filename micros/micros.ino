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
//Lux
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
//UV
Adafruit_SI1145 uv = Adafruit_SI1145();

void setup() {
Serial.begin(9600);
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
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" grados    ");
  Serial.print("UV: ");
  Serial.println(UVindex);
  }

}

//Lux
void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
}

void configureSensor(void)
{
  tsl.enableAutoRange(true);      
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
   tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}
//
