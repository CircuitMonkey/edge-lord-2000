#include "Arduino.h"  
#include "ModeManual.h"

ModeManual::ModeManual(Adafruit_SSD1327& _display) : display(_display) {
    display = _display;
    uint8_t H = 100;
    slider[0]  = new OledSlider(display, "1",  0,127-H,  32,H,  0,15, 0);
    slider[1]  = new OledSlider(display, "2", 32,127-H,  32,H,  0,15, 3);
    slider[2]  = new OledSlider(display, "3", 64,127-H,  32,H,  0,15, 7);
    slider[3]  = new OledSlider(display, "4", 96,127-H,  32,H,  0,15,15);    
}

void ModeManual::draw() {
  display.drawBitmap(  2, 2, glyph, G_WH, G_WH, 15);
  display.setCursor( 36, 8 );
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.println( "Manual Mode" );
  if ( showing < 1 ) return;
  
  for(int i=0; i<4; i++) {
    if ( i == currentSlider ) {
      slider[i]->select(1);
    } else {
      slider[i]->select(0);
    }
    slider[i]->draw();
  }
}

// Process button press
int8_t ModeManual::buttonState(uint8_t _s) {
  // don't process presses if we are not showing.
  //Serial.println("Manual Button State");
  if ( showing < 1 ) return -1;
  if ( (_s&0x01) == 0 ) {
    slider[currentSlider]->change(1);    
    return 0;
  }
  if ( (_s&(1<<1)) == 0 ) { // Down
    slider[currentSlider]->change(-1);
    return 0;
  }
  if ( (_s&(1<<2)) == 0 ) {  // Left
    currentSlider--;
    if ( currentSlider<0 ) currentSlider = 3;
    return 0;
  }
  if ( (_s&(1<<3)) == 0 ) {  // Right
    currentSlider++;
    if ( currentSlider>3 ) currentSlider = 0;
    return 0;
  }
  if ( (_s&(1<<4)) == 0 ) {  // Enter
    Serial.println( "Enter" );
    showing = 0;
    return -1;  // Cause main  menu to display.
  }

    
  return 0;
  
}

uint8_t ModeManual::getSliderVal(uint8_t _n ) {
  return slider[_n]->getVal();
}

//uint8_t ModeManual::isShowing() {
//  if (showing > 0) return 1;
//  return 0;
//}

void ModeManual::setShowing(uint8_t _show) {
  showing = _show;
}
