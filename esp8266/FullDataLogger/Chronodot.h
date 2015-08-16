
#ifndef CHRONODOT_h
#define CHRONODOT_h


void RTCsetup()
{
  setSyncProvider(RTC.get);   // the function to get the time from the RTC 
  if(timeStatus()!= timeSet) {
     Serial.println("Unable to sync with the RTC");
  } else {
     Serial.println("RTC has set the system time");      
  }
}


time_t getUNIXtime() {
  return now();
}



#endif




