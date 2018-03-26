// Samples ADC at 250Hz (4ms)

#define PERIOD 4000  // period in us

unsigned long last_us = 0L;
unsigned long starttime = 0L;
unsigned long endtime = 0L;
const int heartPin = A1;

void setup (){
  Serial.begin(115200);
}


void loop (){
  if (micros () - last_us > PERIOD){
    last_us += PERIOD ;
    sample () ;
  }
}

void sample (){
  int heartValue = analogRead(heartPin); 
  Serial.println(heartValue);
}
