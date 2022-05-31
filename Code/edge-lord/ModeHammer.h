#ifndef ModeHammer_h 
#define ModeHammer_h

#include "Mode.h"

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"


// Main Mode selection screen
class ModeHammer : public Mode  {
    public:
       ModeHammer(Adafruit_SSD1327& _display);
       void draw();
       void tick();
       int8_t buttonState(uint8_t _s);
       uint8_t getMotorVal(uint8_t _n );
     private:
       int8_t currentSlider = 0;
       static const uint8_t N_SLIDERS = 4;
       OledSlider *slider[N_SLIDERS];
       const unsigned char* glyph = glyph16m_hammer;
       static const uint8_t ANIM_STEPS = 128;
       uint8_t animStep = 0;
       //uint8_t animTable[ANIM_STEPS][2]; // states for 2 motors (upper-Lower)
       //void calcAnim();
       void resetAnim();
};

#endif
