#include "Arduino.h"  
#include "ModeMenu.h"
#include "OledGlyphs.h"

#define D_GAP 12
#define DY 40
//#define DY 24
//#define G_WH 16
#define G_BRIGHT 6
#define G_BRIGHT_S 15
#define B_ROUND 4
#define B_BGND 2
#define MARGIN 4

#define ROWS 3
#define COLS 4

const unsigned char* glyph[ROWS*COLS];

ModeMenu::ModeMenu(Adafruit_SSD1327& _display) : display(_display) {
    display = _display;

    // Row 1
    glyph[0] = glyph16m_sliders;
    glyph[1] = glyph16m_cycle;
    glyph[2] = glyph16m_left_right;
    glyph[3] = glyph16m_up_down;

    // Row 2
    glyph[4] = glyph16m_crossing;
    glyph[5] = glyph16m_dice;
    glyph[6] = glyph16m_pattern_01;
    glyph[7] = glyph16m_pattern_02;

    glyph[8] = glyph16m_pattern_03;
    glyph[9] = glyph16m_blank;
    glyph[10] = glyph16m_blank;
    glyph[11] = glyph16m_blank;
}

void ModeMenu::draw() {
  if ( showing < 1 ) return;
  for ( int i=0; i<ROWS*COLS; i++ ) {
    int x = (G_WH+D_GAP)*(i%COLS) + D_GAP;
    int y = DY + (i/(ROWS+1))*(G_WH+D_GAP);

    int bright = G_BRIGHT;
    if ( i == selected ) bright = G_BRIGHT_S;
    // backdrop for icon
    display.fillRoundRect(x-MARGIN, y-MARGIN, G_WH + 2*MARGIN, G_WH + 2*MARGIN,  B_ROUND, B_BGND);
    // draw icon
    display.drawBitmap(  x, y, glyph[i], G_WH, G_WH, bright);
    // draw selection box around icon
    if ( i == selected ) {
      display.drawRoundRect(x-MARGIN, y-MARGIN, G_WH + 2*MARGIN, G_WH + 2*MARGIN,  B_ROUND, bright);
    }
    
  }
}

void ModeMenu::setSelection(uint8_t _v) {

}

uint8_t ModeMenu::getSelection() {
  return 0;
}

uint8_t ModeMenu::isShowing() {
  if (showing > 0) return 1;
  return 0;
}

void ModeMenu::setShowing(uint8_t _show) {
  showing = _show;
}

int8_t ModeMenu::buttonState(uint8_t _s) {  // U, D, L, R, ENT, STOP
  // don't process presses if we are not showing.
  if ( showing < 1 ) return -1;
  if ( (_s&0x01) == 0 ) {
    if ( selected < COLS ) {  // Up
      selected += (ROWS-1)*COLS;
    } else {
      selected -= COLS;
    }
    return -1;
  }
  if ( (_s&(1<<1)) == 0 ) { // Down
    if ( selected < (ROWS-1)*COLS ) {
      selected += COLS;
    } else {
      selected -= (ROWS-1)*COLS;
    }
    return -1;
  }
  if ( (_s&(1<<2)) == 0 ) {  // Left
    if ( (selected%COLS) > 0 ) {
      selected -= 1;
    } else {
      //selected -= 1;
      selected += COLS-1;
    }
    return -1;
  }
  if ( (_s&(1<<3)) == 0 ) {  // Right
    if ( (selected%COLS) == COLS-1 ) {
      selected -= COLS-1;
    } else {
      selected += 1;
    }
    return -1;
  }
  if ( (_s&(1<<4)) == 0 ) {  // Enter
    Serial.println( "Enter" );
    showing = 0;
    return selected;
  }
  return -1;
}
