#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1327.h>
#include "OledSlider.h"

#include "ModeMenu.h"
#include "ModeManual.h"
#include "ModeCycle.h"
#include "ModeLeftRight.h"

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
#define MOT_2  5
#define MOT_1  18

#define MOT_MAX 80
// Slider range 0-15  versus motor range 0-255
// motor = slider * MOT_GAIN
#define MOT_GAIN  6

uint8_t buttonState = 0xFF;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// I2C OLED ::  SDA = 21,  SCK = 22,  RST = 15
const uint8_t OLED_RESET = 15;
Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);
//OledSlider *slider[4];
//OledSlider slider1(display, 0,64,0,15,0);
//OledSlider slider2(display, 32,64,0,15,3);
//OledSlider slider3(display, 64,64,0,15,7);
//OledSlider slider4(display, 96,64,0,15,15);

ModeMenu menu(display);
ModeManual modeManual(display);
ModeCycle modeCycle(display);
ModeLeftRight modeLeftRight(display);

int state = -1;   // -1  Menu : 0-n are vibe modes.

// setting PWM properties
const int FREQ = 512;
const int RESOLUTION = 8;

void setup() {
  Serial.begin(115200);
  while (! Serial) delay(100);
  Serial.println("SSD1327 OLED test");
  
  if ( ! display.begin(0x3D) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  display.clearDisplay();
  display.display();

  showStartScreen();
  menu.setShowing(1);
  menu.draw();
  
  // Power to LEDs must be enabled
  pinMode(LED_ENABLE, OUTPUT);
  digitalWrite(LED_ENABLE, HIGH);

  pinMode(BTN_U, INPUT_PULLUP);
  pinMode(BTN_D, INPUT_PULLUP);
  pinMode(BTN_L, INPUT_PULLUP);
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_ENT, INPUT_PULLUP);
  pinMode(BTN_STP, INPUT_PULLUP);

  
    // configure LED PWM functionalitites
  ledcSetup(0, FREQ, RESOLUTION);
  ledcSetup(1, FREQ, RESOLUTION);
  ledcSetup(2, FREQ, RESOLUTION);
  ledcSetup(3, FREQ, RESOLUTION);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(MOT_1, 0);
  ledcAttachPin(MOT_2, 1);
  ledcAttachPin(MOT_3, 2);
  ledcAttachPin(MOT_4, 3);
  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  
  readButtons();
  // DEBUG: Button state display
  //display.fillRect(0, 8, 40, 8, 0);
  //display.setCursor(0,8);
  //display.println( buttonState, BIN );

  if ( state < 0 ) {
    state = menu.buttonState(buttonState);
    if ( state < 0 ) {
      //Serial.println("Menu");
      menu.draw();
    } else {
      switch( state ) {
        case 0: modeManual.setShowing(1);
          break;
        case 1: modeCycle.setShowing(1);
          break;        
        case 2: modeLeftRight.setShowing(1);
          break;        
      }
      display.clearDisplay();
    }
  } else {  // Non main-menu modes
    switch ( state ) {
      case 0: // Mode Manual
        if ( modeManual.buttonState(buttonState) < 0 ) {
          // back to menu
          //Serial.println("ManualMenu exited.");
          state = -1;
          setOutputs( 0,0,0,0 );
          modeManual.setShowing( 0 );
        } else {
          //Serial.println("Normal Manual Menu");
          modeManual.draw();
          setOutputs(
            modeManual.getSliderVal(0)*MOT_GAIN,
            modeManual.getSliderVal(1)*MOT_GAIN,
            modeManual.getSliderVal(2)*MOT_GAIN,
            modeManual.getSliderVal(3)*MOT_GAIN
          );
          modeManual.draw(); // Normal mode state.
        }
        break;
      case 1: // Mode Cycle
        if ( modeCycle.buttonState(buttonState) < 0 ) {
          // back to menu
          //Serial.println("ManualMenu exited.");
          state = -1;
          setOutputs( 0,0,0,0 );
          modeCycle.setShowing( 0 );
        } else {
          //Serial.println("Normal Manual Menu");
          // todo get mode outputs as array
          modeCycle.bumpAnimStep();
          setOutputs(
            modeCycle.getMotorVal(0)*MOT_GAIN,
            modeCycle.getMotorVal(1)*MOT_GAIN,
            modeCycle.getMotorVal(2)*MOT_GAIN,
            modeCycle.getMotorVal(3)*MOT_GAIN
          );
          modeCycle.draw();
        }
        break;
      case 2: // Mode Left-Right
        if ( modeLeftRight.buttonState(buttonState) < 0 ) {
          // back to menu
          //Serial.println("modeLeftRight exited.");
          state = -1;
          setOutputs( 0,0,0,0 );
          modeLeftRight.setShowing( 0 );
        } else {
          //Serial.println("Normal Manual Menu");
          // todo get mode outputs as array
          modeLeftRight.bumpAnimStep();
          setOutputs(
            modeLeftRight.getMotorVal(0)*MOT_GAIN,
            modeLeftRight.getMotorVal(1)*MOT_GAIN,
            modeLeftRight.getMotorVal(2)*MOT_GAIN,
            modeLeftRight.getMotorVal(3)*MOT_GAIN
          );
          modeLeftRight.draw();
        }
        break;
      default:
        state = -1;
    }
    if ( state < 0 ) {
      //Serial.println( "Mode switched to menu.");
      display.clearDisplay();
      menu.setShowing(1);
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
//  display.setTextSize(1);
//  display.setTextColor(SSD1327_WHITE);
//  display.println("press the buttons...");  
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
    ledcWrite(0, a);
    ledcWrite(1, b);
    ledcWrite(2, c);
    ledcWrite(3, d);
  setLED( 1, 0, a, b );
  setLED( 2, 0, c, d );

  // LED near STOP button is green when there is any motor running
  // otherwise it turns yellow.
  if ( a > 0  || b > 0 || c > 0 || d > 0  ) {
    setLED(0, 0, 200, 0 );
  } else {
    setLED(0, 200, 150, 0 );
  }
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
