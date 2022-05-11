#ifndef OledSlider_h 
#define OledSlider_h

#include <Adafruit_SSD1327.h>

#include "Arduino.h"

class OledSlider {
    public:
       OledSlider(Adafruit_SSD1327& _display, String _title, uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _minV, uint8_t _maxV, uint8_t _curV);
       
       //void begin(Adafruit_SSD1327* display);
       void draw();
       void setVal(uint8_t _v);
       uint8_t getVal();
       void change(int8_t _amt );
       void select(uint8_t _s);
       uint8_t isSelected();
     protected:
       Adafruit_SSD1327& display;
     private:
       String title;
       uint8_t x;
       uint8_t y;
       uint8_t w;
       uint8_t h;
       uint8_t minV;
       uint8_t maxV; 
       int8_t curV;
       uint8_t selected = 0;
};

#endif
