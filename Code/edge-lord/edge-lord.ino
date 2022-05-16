#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1327.h>
#include "OledSlider.h"

#include "ModeMenu.h"
#include "ModeManual.h"
#include "ModeCycle.h"
#include "ModeLeftRight.h"
#include "ModeBlank.h"

#include "OledGlyphs.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  3
#define LED_ENABLE 4

#define BTN_U 15
#define BTN_D 14
#define BTN_L 27
#define BTN_R 21
#define BTN_STP 13
#define BTN_ENT 32

// Wired the connector in the reverse order, so
// we flip the signals around here.  Fix in Rev. B
#define MOT_4  A0
#define MOT_3  A1
#define MOT_2  18
#define MOT_1  19

#define MOT_MIN 6
#define MOT_MAX 48
// Slider range 0-15  versus motor range 0-255
// motor = slider * MOT_GAIN
#define MOT_GAIN  MOT_MAX/16

uint8_t buttonState = 0xFF;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// I2C OLED ::  SDA = 21,  SCK = 22,  RST = 15
const uint8_t OLED_RESET = 36;
Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);

ModeMenu menu(display);
ModeManual modeManual(display);
ModeCycle modeCycle(display);
ModeLeftRight modeLeftRight(display);
ModeBlank modeBlank(display);

Mode *mode[12];

int state = -1;   // -1  Menu : 0-n are vibe modes.

// setting PWM properties
const int FREQ = 256;
const int RESOLUTION = 8;

void setup() {
  Serial.begin(115200);
  while (! Serial) delay(100);
  Serial.println("EdgeLord 2000");
  
  if ( ! display.begin(0x3D) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  display.clearDisplay();
  display.display();

  mode[ 0] = &modeManual;  // mode[0] = new ModeManual(display);  ???
  mode[ 1] = &modeCycle;
  mode[ 2] = &modeLeftRight;
//  mode[ 3] = &modeUpDown;
//  mode[ 4] = modeCross;
//  mode[ 5] = modeRandom;
//  mode[ 6] = modePat1;
//  mode[ 7] = modePat2;
//  mode[ 8] = modePat3;
//  mode[ 9] = modePat4;
//  mode[10] = modePat5;
//  mode[11] = modePat6;
  mode[ 3] = &modeBlank;
  mode[ 4] = &modeBlank;
  mode[ 5] = &modeBlank;
  mode[ 6] = &modeBlank;
  mode[ 7] = &modeBlank;
  mode[ 8] = &modeBlank;
  mode[ 9] = &modeBlank;
  mode[10] = &modeBlank;
  mode[11] = &modeBlank;

  showStartScreen();
  menu.setShowing(1);
  menu.draw();
  
  // Power to LEDs must be enabled
  pinMode(LED_ENABLE, OUTPUT);
  digitalWrite(LED_ENABLE, HIGH);

  // Configure buttons
  pinMode(BTN_U, INPUT_PULLUP);
  pinMode(BTN_D, INPUT_PULLUP);
  pinMode(BTN_L, INPUT_PULLUP);
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_ENT, INPUT_PULLUP);
  pinMode(BTN_STP, INPUT_PULLUP);
  
  // configure Motor PWM channels
  ledcSetup(0, FREQ, RESOLUTION);
  ledcSetup(1, FREQ, RESOLUTION);
  ledcSetup(2, FREQ, RESOLUTION);
  ledcSetup(3, FREQ, RESOLUTION);
  
  // attach the Motor GPIO to PWM channels
  ledcAttachPin(MOT_1, 0);
  ledcAttachPin(MOT_2, 1);
  ledcAttachPin(MOT_3, 2);
  ledcAttachPin(MOT_4, 3);
  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  setOutputs( 0, 0, 0, 0 );
}


void loop() {
  
  readButtons();
  // DEBUG: Button state display
  //display.fillRect(0, 8, 40, 8, 0);
  //display.setCursor(0,8);
  //display.println( buttonState, BIN );

  if ( state < 0 ) {
    // Handle Main Menu button presses
    state = menu.buttonState(buttonState);
    if ( state < 0 ) {
      //Serial.println("Menu");
      menu.draw();
    } else {
      //menu.setShowing(0);
      mode[state]->setShowing(1);
      display.clearDisplay();
    }
    setOutputs(0,0,0,0);
  } else {  // Non main-menu modes
    if ( mode[state]->buttonState(buttonState) < 0 ) {
        // user exited state. back to menu.
        state = -1;
        setOutputs( 0,0,0,0 );  // turn off motors
        //mode[state]->setShowing( 0 );  // stop showing mode
        display.clearDisplay();
        menu.setShowing(1); // enable main menu
        menu.draw();
    } else {
        mode[state]->tick();
        setOutputs(
          mode[state]->getMotorVal(0)*MOT_GAIN,
          mode[state]->getMotorVal(1)*MOT_GAIN,
          mode[state]->getMotorVal(2)*MOT_GAIN,
          mode[state]->getMotorVal(3)*MOT_GAIN
        );
        mode[state]->draw(); // Normal mode state.
    }
  }

  display.display();
  strip.show();
  delay(70);
}

void showStartScreen() {
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1327_BLACK, SSD1327_WHITE); // 'inverted' text
  display.println("    EdgeLord 2000    ");
  display.display();
}

void readButtons() {
  buttonState = digitalRead(  BTN_U )&0x1 | 
                (digitalRead( BTN_D )&0x1) << 1 | 
                (digitalRead( BTN_L )&0x1) << 2 |
                (digitalRead( BTN_R )&0x1) << 3 |
                (digitalRead( BTN_ENT )&0x1) << 4 |
                (digitalRead( BTN_STP )&0x1) << 5;
}

void setOutputs( uint8_t a, uint8_t b, uint8_t c, uint8_t d ) {
    if( a > 0 ) a+= MOT_MIN;
    if( b > 0 ) b+= MOT_MIN;
    if( c > 0 ) c+= MOT_MIN;
    if( d > 0 ) d+= MOT_MIN;
    ledcWrite(0, a);
    ledcWrite(1, b);
    ledcWrite(2, c);
    ledcWrite(3, d);

  // LED near STOP button is yellow when there is any motor running
  // otherwise it turns yellow.
  if ( a > 0  || b > 0 || c > 0 || d > 0  ) {
    setLED(0, 200, 200, 0 );
  } else {
    setLED(0, 200, 50, 0 );
  }
  
  setLED( 1, 1, a+1, b+1 );
  setLED( 2, 1, c+1, d+1 );
}

void setLED( int n, uint8_t r, uint8_t g, uint8_t b ) {
  strip.setPixelColor(n, strip.Color(r,g,b));
}


void blankLEDs() {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(0, 0, 0));       //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
}
