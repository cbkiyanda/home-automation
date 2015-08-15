

#ifndef MPL115A2_h
#define MPL115A2_h


void setup_MPL115A2(Adafruit_MPL115A2 *mpl115a2) {
  mpl115a2->begin();
}


void getPT(Adafruit_MPL115A2 *mpl115a2, float *pressureKPA, float *temperatureC) {
  //  float pressureKPA = 0, temperatureC = 0;    
  mpl115a2->getPT(pressureKPA,temperatureC);
}





#endif



