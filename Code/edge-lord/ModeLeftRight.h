#ifndef ModeLeftRight_h 
#define ModeLeftRight_h

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"

#define MODE_LEFT_RIGHT_ANIM_STEPS 64

// Main Mode selection screen
class ModeLeftRight {
    public:
       ModeLeftRight(Adafruit_SSD1327& _display);
       void draw();
       int8_t buttonState(uint8_t _s);
       uint8_t getMotorVal(uint8_t _n );
       void setShowing(uint8_t _show);
       void calcAnim();
       void bumpAnimStep();
       void resetAnim();
     protected:
       Adafruit_SSD1327& display;
     private:
       uint8_t showing = 0;
       int8_t currentSlider = 0;
       OledSlider *slider[5];
       const unsigned char* glyph = glyph16m_left_right;
       String LBL_UP = "UP";
       String LBL_DN = "DOWN";
       String LBL_SPD = "SPD";
       String LBL_HRD = "HARD";
       uint8_t animStep = 0;
       uint8_t animTable[64][2]; // 64 states for 2 motors (upper-Lower)
};

#endif
