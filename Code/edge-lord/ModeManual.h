#ifndef ModeManual_h 
#define ModeManual_h

#include <Adafruit_SSD1327.h>

#include "Arduino.h"
#include "OledSlider.h"
#include "OledGlyphs.h"

// Main Mode selection screen
class ModeManual {
    public:
       ModeManual(Adafruit_SSD1327& _display);
       void draw();
       int8_t buttonState(uint8_t _s);
       uint8_t getSliderVal(uint8_t _n );
//       uint8_t isShowing();
       void setShowing(uint8_t _show);
     protected:
       Adafruit_SSD1327& display;
     private:
       uint8_t showing = 0;
       int8_t currentSlider = 0;
       OledSlider *slider[4];
       const unsigned char* glyph = glyph16m_sliders;
};

#endif
