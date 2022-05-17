#include "Arduino.h"  
#include "ModeLeftRight.h"

ModeLeftRight::ModeLeftRight(Adafruit_SSD1327& _display) : Mode( _display ) {
    uint8_t H = 100;
    uint8_t W = 127/N_SLIDERS;
    slider[0]  = new OledSlider(display, "U",   W*0,127-H, W,H,  0,15,  4);  // Upper
    slider[1]  = new OledSlider(display, "L",   W*1,127-H, W,H,  0,15,  4);  // Lower
    slider[2]  = new OledSlider(display, "SPD", W*2,127-H, W,H,  1,12,  4);  // Speed

    calcAnim();
}

void ModeLeftRight::draw() {
  display.drawBitmap(  2, 2, glyph, G_WH, G_WH, 15);
  display.setCursor( 36, 8 );
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.println( "Left-Right" );
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
int8_t ModeLeftRight::buttonState(uint8_t _s) {
  // don't process presses if we are not showing.
  //Serial.println("Manual Button State");
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
    if ( currentSlider<0 ) currentSlider = 4;
    return 0;
  }
  if ( (_s&(1<<3)) == 0 ) {  // Right
    currentSlider++;
    if ( currentSlider>4 ) currentSlider = 0;
    return 0;
  }
  if ( (_s&(1<<4)) == 0 ) {  // Enter
    //Serial.println( "Left-Right Enter" );
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

uint8_t ModeLeftRight::getMotorVal(uint8_t _n ) {
  if ( stopped ) return 0;
  
  return animTable[animStep][_n%2] * slider[_n/2]->getVal() / 16;  // two upper - two lower left-right?
}

// Recompute animation table
void ModeLeftRight::calcAnim() {
  //  Re calc table.  If speed changed, then we need to set the animStep to the closest match
  //  to the previous values to avoid "jarring" motor changes to user.

  // zereo the table
  for ( int i=0; i< ANIM_STEPS; i++ ) {
    animTable[i][0] = 0;
    animTable[i][1] = 0;
  }
  // Wave table
  for ( int i=0; i< ANIM_STEPS; i++ ) {
    int ix1 = (i+ANIM_STEPS*1/2)%ANIM_STEPS;
    
    float cs = sin( 2.0* PI * ((float)i/ANIM_STEPS/2));
    if ( cs < 0 ) cs = 0; // clamp negative
    
    animTable[i][0] = cs * 15;
    animTable[ix1][1] = animTable[i][0];
  }
  for ( int i=0; i< ANIM_STEPS; i++ ) {
    Serial.print( 0 ); Serial.print( ":");
    Serial.print( animTable[i][0]); Serial.print( "  ");
    Serial.print( 1 ); Serial.print( ":");
    Serial.print( animTable[i][1]); Serial.print( "  ");
    Serial.println();
  }
  
}

void ModeLeftRight::tick() {
  if ( stopped ) return;
  animStep += (int)(1.5 * slider[2]->getVal());
  if ( animStep >= ANIM_STEPS ) {
    resetAnim();
  }
}

void ModeLeftRight::resetAnim() {
  animStep = 0;
}
