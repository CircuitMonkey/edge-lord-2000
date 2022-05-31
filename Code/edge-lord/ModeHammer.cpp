#include "Arduino.h"  
#include "ModeHammer.h"

ModeHammer::ModeHammer(Adafruit_SSD1327& _display) : Mode( _display ) {
    const static uint8_t H = 100;
    const static uint8_t W = 127/N_SLIDERS;
    slider[0]  = new OledSlider(display, "U",    W*0,127-H, W,H,  0,15,  2);  // Upper
    slider[1]  = new OledSlider(display, "L",    W*1,127-H, W,H,  0,15,  2);  // Lower
    slider[2]  = new OledSlider(display, "DUTY", W*2,127-H, W,H,  1,16,  6);  // On-time
    slider[3]  = new OledSlider(display, "FREQ", W*3,127-H, W,H,  1,16,  4);  // Freq

    //calcAnim();
}

void ModeHammer::draw() {
  display.drawBitmap(  2, 2, glyph, G_WH, G_WH, 15);
  display.setCursor( 36, 8 );
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.println( "Hammer" );
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
int8_t ModeHammer::buttonState(uint8_t _s) {
  // don't process presses if we are not showing.
  //Serial.println("Cross Button State");
  if ( showing < 1 ) return -1;
  if ( (_s&0x01) == 0 ) {
    slider[currentSlider]->change(1);
    //calcAnim();  
    return 0;
  }
  if ( (_s&(1<<1)) == 0 ) { // Down
    slider[currentSlider]->change(-1);
    //calcAnim();
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
    Serial.println( "UpDown Enter" );
    showing = 0;
    return -1;  // Cause main  menu to display.
  }
  if ( (_s&(1<<5)) == 0 ) {  // Stop/pause
    stopped = !stopped;  // toggle stop state
    //Serial.println( "Left-Right STOP button pressed" );
    return 0;
  }

  return 0;  
}

uint8_t ModeHammer::getMotorVal(uint8_t _n ) {
  if ( stopped ) return 0;

  // If animStep less than DUTY, turn on.
  if ( animStep>(slider[2]->getVal()-1)*6 ) return 0; // only on during duty-cycle range.

  int mot = _n/2; //  0=upper,  1=lower
  return slider[mot]->getVal();
  
}

void ModeHammer::tick() {
  if ( stopped ) return;
  animStep++;
  animStep += (int)((slider[3]->getVal()-1) * 7 );  // 1 - 8
  if ( animStep >= ANIM_STEPS ) {
    resetAnim();
  }
}

void ModeHammer::resetAnim() {
  animStep = 0;
}
