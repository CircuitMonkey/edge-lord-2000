#include "Arduino.h"  
#include "OledSlider.h"
 


OledSlider::OledSlider(
        Adafruit_SSD1327& _display, String _title, 
        uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, 
        uint8_t _minV, uint8_t _maxV, uint8_t _curV    ) : display(_display) { 
    display = _display;
    title = _title;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    minV = _minV;
    maxV = _maxV;
    curV = _curV;

}

void OledSlider::setVal( uint8_t v) {
    if ( v < minV ) return;
    if ( v > maxV ) return;
    curV = v;
}

uint8_t OledSlider::getVal() { 
    return curV;
}

void OledSlider::change(int8_t _amt) {
  curV += _amt;
  if ( curV < minV ) curV = minV;
  if ( curV > maxV ) curV = maxV;
}

void OledSlider::select(uint8_t _s) {
  selected = _s;
}

uint8_t OledSlider::isSelected() {
  if ( selected > 0 ) return true;
  return false;
}

void OledSlider::draw() {
    uint8_t BORDER=1;
    uint8_t TXT_H = 10;
    uint8_t SLD_Y = y + 2*TXT_H;
    uint8_t SLD_H = h - 2*TXT_H;
    uint8_t GW=2;
    uint8_t GT=10;
    uint8_t GH=SLD_H-GT*2;
    uint8_t BW=w/3;
    uint8_t BH=w/6;
    // render slider
    // backdrop
    display.fillRect(x+BORDER, y+BORDER, w-2*BORDER, h-2*BORDER, 2);
    // title label
    display.fillRect(x+BORDER, y+BORDER, w-2*BORDER, TXT_H, 5);
      
    // Bold print - double print offset by one.
    uint16_t offSet = title.length()*6/2;  // help center the text
    display.setCursor(x+w/2-offSet+1,y+BORDER+1);
    display.setTextSize(1);
    display.setTextColor(13);
    display.print( title );
    // brighter - non-offset text over lighter text
    display.setCursor(x+w/2-offSet,y+BORDER+1);
    display.setTextSize(1);
    display.setTextColor(15);
    display.print( title );

    // text backdrop
    display.setCursor(x+w/2-4,y+BORDER+1+TXT_H);
    display.fillRect(x+BORDER, y+BORDER+TXT_H, w-2*BORDER, TXT_H, 3);    
    display.setTextSize(1);
    display.setTextColor(10);
    display.print( curV );
    // groove
    display.fillRect(x+w/2-2, SLD_Y+GT, GW, GH, 4);
    // button base
    float bStep = (float)GH/(maxV-minV);  // pixel/sub-pixel change per input value increment
    uint8_t bY = (uint8_t)(bStep*(maxV-curV));
    display.fillRect(x+w/2-BW/2, SLD_Y+GT+bY-BH/2, BW, BH,  12);

    if (isSelected()) {
       display.fillTriangle(
               x+w/2, y+h-2*BORDER-6,
               x+w/2+4, y+h-2*BORDER-1,
               x+w/2-4, y+h-2*BORDER-1,  14);
    }
    
} 
  
