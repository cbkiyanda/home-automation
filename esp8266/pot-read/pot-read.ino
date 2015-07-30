int analogPin = 1;     // potentiometer wiper (middle terminal) connected to analog pin A

                       // outside leads to ground and +3.3V

int val = 0;           // variable to store the value read



void setup()

{

  Serial.begin(115200);          //  setup serial
  
}



void loop()

{
  val = 0;
  int i = 0;
   for (i=0; i <= 50; i++){
      val = val + analogRead(A0);
      delay(10);
   }

  Serial.println( (double)val/(double)i);             // debug value
  delay(2000);
}
