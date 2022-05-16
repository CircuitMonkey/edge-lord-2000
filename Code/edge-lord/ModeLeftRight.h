#ifndef ModeLeftRight_h 
#define ModeLeftRight_h

#include "Mode.h"

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"

#define MODE_LEFT_RIGHT_ANIM_STEPS 64

// Main Mode selection screen
class ModeLeftRight : public Mode  {
    public:
       ModeLeftRight(Adafruit_SSD1327& _display);
       void draw();
       void tick();
       int8_t buttonState(uint8_t _s);
       uint8_t getMotorVal(uint8_t _n );
     private:
       int8_t currentSlider = 0;
       static const uint8_t N_SLIDERS = 4;
       OledSlider *slider[N_SLIDERS];
       const unsigned char* glyph = glyph16m_left_right;
       uint8_t animStep = 0;
       uint8_t animTable[64][2]; // 64 states for 2 motors (upper-Lower)
       void calcAnim();
       void resetAnim();
};

#endif
