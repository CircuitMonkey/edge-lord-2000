#ifndef ModeManual_h 
#define ModeManual_h

#include "Mode.h"

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"

// Main Mode selection screen
class ModeManual : public Mode {
    public:
       ModeManual(Adafruit_SSD1327& _display);
       void draw();
       void tick();
       int8_t buttonState(uint8_t _s);
       uint8_t getMotorVal(uint8_t _n );
     private:
       static const uint8_t N_SLIDERS = 4;
       int8_t currentSlider = 0;
       OledSlider *slider[N_SLIDERS];
       const unsigned char* glyph = glyph16m_sliders;
};

#endif
