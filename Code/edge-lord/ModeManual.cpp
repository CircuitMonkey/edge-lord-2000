#include "Arduino.h"  
#include "ModeManual.h"

ModeManual::ModeManual(Adafruit_SSD1327& _display) : Mode( _display ) {
//    display = _display;
    uint8_t H = 100;
    uint8_t W = 127/N_SLIDERS;
    slider[0]  = new OledSlider(display, "1",  W*0,127-H,  W,H,  0,15, 0);
    slider[1]  = new OledSlider(display, "2",  W*1,127-H,  W,H,  0,15, 0);
    slider[2]  = new OledSlider(display, "3",  W*2,127-H,  W,H,  0,15, 0);
    slider[3]  = new OledSlider(display, "4",  W*3,127-H,  W,H,  0,15, 0);    
}

void ModeManual::draw() {
  display.drawBitmap(  2, 2, glyph, G_WH, G_WH, 15);
  display.setCursor( 36, 8 );
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.println( "Manual" );
  if ( showing < 1 ) return;
  
  for(int i=0; i<N_SLIDERS; i++) {
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
    if ( currentSlider<0 ) currentSlider = N_SLIDERS-1;
    return 0;
  }
  if ( (_s&(1<<3)) == 0 ) {  // Right
    currentSlider++;
    if ( currentSlider>=N_SLIDERS ) currentSlider = 0;
    return 0;
  }
  if ( (_s&(1<<4)) == 0 ) {  // Enter
    Serial.println( "Enter" );
    showing = 0;
    return -1;  // Cause main  menu to display.
  }

    
  return 0;
  
}

uint8_t ModeManual::getMotorVal(uint8_t _n ) {
  if ( stopped ) return 0;
  return slider[_n]->getVal();
}

void ModeManual::tick() {}
