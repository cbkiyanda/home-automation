

// Created Brian Larsen
// 20150815
// balarsen@gmail.com
//
// Style note, written to be as modular as possible
//   everything needed for each sensor is seperate
//   and repeated to allow for copy and paste
//
// Much of the code below comes from adafruit libraries
//   and examples. All are under BSD license as is this


/*****************************************************
 * Chronodot - Battery backup RTC
 *     This provides the time over reset and all time
 *     Need to figure out how to set the time a first 
 *     run to a time we like, or maybe when one holds 
 *     in a button it is set via internet...
 *    Returns: Use the unixtime as the stamp for data
*****************************************************/
/*****************************************************
 * TSL2561 - Lux sensor
 *     This gives the light output that will be logged
 *     There is nothing special that needs to be done
 *     here just grab the data and store it.
 *    Returns: Lux values 
 *****************************************************/
/*****************************************************
 * I2C FRAM - Data storage 
 *     This provides 32kbytes of storage that will be  
 *     used in a stack configuration. Data is written
 *     periodically and then on readout it is read and
 *     transmitted over the wifi
 *    Returns: stored data
 *****************************************************/
/*****************************************************
 * MPL115A2 - Temperature and pressure
 *     This onboard measures the temperature and
 *     pressure. This measurment will be inside the box
 *     so this is not the most accurate, likely will 
 *     have to add a remote thmermistor measurement 
 *     outside of the box
 *    Returns: Temperature and pressure
 *****************************************************/
/*****************************************************
 * WiFi - 
 *     need to connect and dump data to a server over
 *     the wifi periodically
 *****************************************************/
// * TSL2561 - Lux sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <pgmspace.h>
#include "TSL2561.h"
Adafruit_TSL2561_Unified tsl2562 = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 0x39);
// * MPL115A2 - Temperature and pressure
#include <Wire.h>
#include <Adafruit_MPL115A2.h>
#include "MPL115A2.h"
Adafruit_MPL115A2 mpl115a2;

 
void setup() {
  Serial.begin(115200);
  Wire.begin(0,2); // SDA, SCL

  // * TSL2561 - Lux sensor
  setup_TSL2561(&tsl2562);
  // * MPL115A2 - Temperature and pressure
  setup_MPL115A2(&mpl115a2);
}

void loop() {
  // * TSL2561 - Lux sensor
  Serial.print(getLUX(&tsl2562)); Serial.println(" lux");
  // * MPL115A2 - Temperature and pressure
  float pressureKPA = 0, temperatureC = 0;
  getPT(&mpl115a2, &pressureKPA, &temperatureC);
  Serial.print("Pressure: "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
  Serial.print("Temp: "); Serial.print(temperatureC, 1); Serial.println(" *C");



  
  delay(3000);
}
