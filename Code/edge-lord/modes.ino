
//
//void setVibes(int val1, int val2) {
//  int mot1Val = val1 * MOT_MAX/10;
//  if (ch1Value == 1) { // Kick the motor
//    analogWrite(MOT_1, mot1Val + 20);
//    delay(1);
//  }
//  analogWrite(MOT_1, mot1Val);
//
//  int mot2Val = val2 * MOT_MAX/10;
//  if (ch2Value == 1) { // Kick the motor
//    analogWrite(MOT_2, mot2Val + 20);
//    delay(1);
//  }
//  analogWrite(MOT_2, mot2Val);
//}
//
//
//long pingCount = 0;
//int pp = 0;
//void pingPong( long nPings, int val1, int val2) {
//  if ( pingCount > 0 ) {
//    pingCount--;
//    return;
//  } else {
//    pp = 1 - pp; // Toggle pp
//    pingCount = nPings;
//  }
//  if ( pp < 1 ) { // ping
//    setVibes(val1, 0);
//  } else {        // pong
//    setVibes(0, val2);
//  }
//}
