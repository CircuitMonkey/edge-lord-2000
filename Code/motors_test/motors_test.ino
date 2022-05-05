

#define MOT_1  A0
#define MOT_2  A1
#define MOT_3  5
#define MOT_4  18

const int MCOUNT = 100;

int activeMot = 0;
int count = 0;

int mot1Val = 0;
int mot2Val = 0;
int mot3Val = 0;
int mot4Val = 0;


// setting PWM properties
const int freq = 100;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcSetup(3, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(MOT_1, 0);
  ledcAttachPin(MOT_2, 1);
  ledcAttachPin(MOT_3, 2);
  ledcAttachPin(MOT_4, 3);
}


void loop() {
    ledcWrite(0, mot1Val);
    ledcWrite(1, mot2Val);
    ledcWrite(2, mot3Val);
    ledcWrite(3, mot4Val);

  count++;
  if ( count > MCOUNT ) {
    count = 0;
  }
  
  if ( count > MCOUNT/2 ) {
    mot1Val = 64;
    mot2Val = 64;
    mot3Val = 64;
    mot4Val = 64;
  } else {
    mot1Val = 0;
    mot2Val = 0;
    mot3Val = 0;
    mot4Val = 0;    
  }

  delay(50);
}
