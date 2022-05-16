#ifndef Mode_h 
#define Mode_h

// Base class Mode
#include <Adafruit_SSD1327.h>

class Mode {
   public:
      Mode(Adafruit_SSD1327& _display) : display(_display)  {
          display = _display;
      }
      
      virtual void draw() = 0;
      virtual void tick() = 0;      
      virtual int8_t buttonState(uint8_t _s) = 0;
      virtual uint8_t getMotorVal(uint8_t _n ) = 0;
      uint8_t getStopped()  {
        return stopped;
      }
      void setShowing(uint8_t _show) {
        showing = _show;
      };
      
   protected:
       Adafruit_SSD1327& display;
       uint8_t showing = 0;
       uint8_t stopped = 0;
};

#endif
