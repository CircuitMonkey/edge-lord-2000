#ifndef ModeBlank_h 
#define ModeBlank_h

#include "Mode.h"

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"

// Main Mode selection screen
class ModeBlank : public Mode {
    public:
       ModeBlank(Adafruit_SSD1327& _display);
       void draw();
       void tick();
       int8_t buttonState(uint8_t _s);
       uint8_t getMotorVal(uint8_t _n );
     private:
       const unsigned char* glyph = glyph16m_blank;
};

#endif
