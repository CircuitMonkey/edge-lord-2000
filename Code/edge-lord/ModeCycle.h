#ifndef ModeCycle_h 
#define ModeCycle_h

#include "Mode.h"

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"

// Main Mode selection screen
class ModeCycle : public Mode {
    public:
       ModeCycle(Adafruit_SSD1327& _display);
       void draw();
       void tick();
       int8_t buttonState(uint8_t _s);
       uint8_t getMotorVal(uint8_t _n );
     private:
       int8_t currentSlider = 0;
       static const uint8_t N_SLIDERS = 4;
       OledSlider *slider[N_SLIDERS];
       const unsigned char* glyph = glyph16m_cycle;
       String LBL_UP = "UP";
       String LBL_DN = "DOWN";
       String LBL_SPD = "SPD";
       String LBL_DIR = "DIR";
       String LBL_HRD = "HARD";
       static const uint8_t ANIM_STEPS = 128;
       uint8_t animStep = 0;
       uint8_t animTable[ANIM_STEPS][4]; // 128 states for 4 motors
       void resetAnim();
       void calcAnim();
};

#endif
