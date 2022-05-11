/*
 * Handle states effected by buttons.
 */

//int lastCh1DownState = 0;
//int ch1DownState = 0;
//int lastCh1UpState = 0;
//int ch1UpState = 0;
//
//int lastCh2DownState = 0;
//int ch2DownState = 0;
//int lastCh2UpState = 0;
//int ch2UpState = 0;
//
//int lastModeDownState = 0;
//int modeDownState = 0;
//int lastModeUpState = 0;
//int modeUpState = 0;
//
//#define CHAN_1_DN  13
//#define CHAN_1_UP  14
//#define CHAN_2_DN  15
//#define CHAN_2_UP  21
//#define MODE_DN    32
//#define MODE_UP    27
//
//#define CHAN_VAL_MAX  9
//#define CHAN_VAL_MIN  0
//
//#define MODE_VAL_MAX  9
//#define MODE_VAL_MIN  0
//
//void initChannels() {
//  pinMode(CHAN_1_DN, INPUT_PULLUP);
//  pinMode(CHAN_1_UP, INPUT_PULLUP);
//  pinMode(CHAN_2_DN, INPUT_PULLUP);
//  pinMode(CHAN_2_UP, INPUT_PULLUP);
//  pinMode(MODE_DN,   INPUT_PULLUP);
//  pinMode(MODE_UP,   INPUT_PULLUP);
//}
//
//void updateChannelState() {
//  ch1DownState=digitalRead(CHAN_1_DN);
//  ch1UpState=digitalRead(CHAN_1_UP);
//  if (lastCh1DownState == 0 && ch1DownState == 1) {    
//    if (ch1Value > CHAN_VAL_MIN) {
//      ch1Value--;
//    }
//  // If both buttons are pressed, ignore up-press.
//  } else if (lastCh1UpState == 0 && ch1UpState == 1) {    
//    if (ch1Value < CHAN_VAL_MAX) {
//      ch1Value++;
//    }
//  }
//  lastCh1DownState = ch1DownState;
//  lastCh1UpState = ch1UpState; 
//
//  ch2DownState=digitalRead(CHAN_2_DN);
//  ch2UpState=digitalRead(CHAN_2_UP);
//  if (lastCh2DownState == 0 && ch2DownState == 1) {    
//    if (ch2Value > CHAN_VAL_MIN) {
//      ch2Value--;
//    }
//  // If both buttons are pressed, ignore up-press.
//  } else if (lastCh2UpState == 0 && ch2UpState == 1) {    
//    if (ch2Value < CHAN_VAL_MAX) {
//      ch2Value++;
//    }
//  }
//  lastCh2DownState = ch2DownState;
//  lastCh2UpState = ch2UpState; 
//
//  modeDownState=digitalRead(MODE_DN);
//  modeUpState=digitalRead(MODE_UP);
//  if (lastModeDownState == 0 && modeDownState == 1) {    
//    if (modeValue > MODE_VAL_MIN) {
//      modeValue--;
//    }
//  // If both buttons are pressed, ignore up-press.
//  } else if (lastModeUpState == 0 && modeUpState == 1) {    
//    if (modeValue < MODE_VAL_MAX) {
//      modeValue++;
//    }
//  }
//  lastModeDownState = modeDownState;
//  lastModeUpState = modeUpState; 
//
//}
