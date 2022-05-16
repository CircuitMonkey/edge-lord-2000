#include "Arduino.h"  
#include "ModeBlank.h"

ModeBlank::ModeBlank(Adafruit_SSD1327& _display) : Mode( _display ) {
}

void ModeBlank::draw() {
  display.drawBitmap(  2, 2, glyph, G_WH, G_WH, 15);
  display.setCursor( 36, 8 );
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.println( "Blank" );
  if ( showing < 1 ) return;
}

// Process button press
int8_t ModeBlank::buttonState(uint8_t _s) {
  //Serial.println("Manual Button State");
  // don't process presses if we are not showing.
  if ( showing < 1 ) return -1;
  if ( (_s&0x01) == 0 ) {
    return 0;
  }
  if ( (_s&(1<<1)) == 0 ) { // Down
    return 0;
  }
  if ( (_s&(1<<2)) == 0 ) {  // Left
    return 0;
  }
  if ( (_s&(1<<3)) == 0 ) {  // Right
    return 0;
  }
  if ( (_s&(1<<4)) == 0 ) {  // Enter
    showing = 0;
    return -1;  // Cause main  menu to display.
  }
  if ( (_s&(1<<5)) == 0 ) {  // Enter
    return 0;  // Cause main  menu to display.
  }

  return 0;  
}

uint8_t ModeBlank::getMotorVal(uint8_t _n ) {
  return 0;
}

void ModeBlank::tick() {}
