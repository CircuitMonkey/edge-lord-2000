#ifndef ModeMenu_h 
#define ModeMenu_h

#include <Adafruit_SSD1327.h>

#include "Arduino.h"

// Main Mode selection screen
class ModeMenu {
    public:
       ModeMenu(Adafruit_SSD1327& _display);
       void draw();       
       void setSelection(uint8_t _v);
       uint8_t getSelection();
       uint8_t isShowing();
       void setShowing(uint8_t _show);
       int8_t buttonState(uint8_t _s);
       void getGlyph(uint8_t i);
     protected:
       Adafruit_SSD1327& display;
     private:
       uint8_t showing = 0;
       uint8_t selected = 0;
};

#endif
