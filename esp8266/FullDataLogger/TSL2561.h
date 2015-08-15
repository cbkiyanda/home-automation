
#ifndef TSL2561_h
#define TSL2561_h


void displaySensorDetails(Adafruit_TSL2561_Unified *tsl)
{
  sensor_t sensor;
  tsl->getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void configureSensor(Adafruit_TSL2561_Unified *tsl)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl->enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  tsl->setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */  
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
}


void setup_TSL2561(Adafruit_TSL2561_Unified *tsl)
{
    /* Initialise the sensor */
  if(!tsl->begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("No TSL2561 detected ... ");
    while(1);
  }
  displaySensorDetails(tsl);
  configureSensor(tsl);
  Serial.println("TSL2561 setup");
}

float getLUX(Adafruit_TSL2561_Unified *tsl)
{
  sensors_event_t event;
  tsl->getEvent(&event); 
  return event.light;
}



#endif



