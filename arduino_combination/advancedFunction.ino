////Functions
void deviceON() {
  matrix.clear();
  strip.setBrightness(127);
  colorWipe(mainColor, 50); //파란색 출력

  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
  for (int8_t x = 7; x >= -36; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Hello");
    matrix.writeDisplay();
    delay(100);
  }
}

void steady() {
  matrix.clear();
  matrix.drawBitmap(0, 0, shape[14], 8, 8, LED_RED);
  matrix.writeDisplay();

  strip.setBrightness(127);
  //rainbowCycle(20);
  whole(mainColor, 50);
}

void showMonth() {
  matrix.clear();
  if (month > 0 && month < 13) {
    matrix.drawBitmap(0, 0, shape[month - 1], 8, 8, LED_GREEN);
    matrix.writeDisplay();
    delay(2000);
  }
}

void playing() {
  matrix.clear();
  matrix.drawBitmap(0, 0, shape[13], 8, 8, LED_GREEN);
  matrix.writeDisplay();

  //  strip.setBrightness(50);
  //  whole(mainColor, 50);
  pointMoving(mainColor, 70, 50, 255);
}

void tempStop() {
  matrix.clear();
  matrix.drawBitmap(0, 0, shape[12], 8, 8, LED_GREEN);
  matrix.writeDisplay();

  whole(mainColor, 1000);
}

void deviceOFF() {
  matrix.clear();

  strip.setBrightness(127);
  whole(red, 1000);
  whole(strip.Color(0, 0, 0), 1000);
  whole(red, 1000);
  whole(strip.Color(0, 0, 0), 1000);
  whole(red, 1000);
  whole(strip.Color(0, 0, 0), 1000);

  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_RED);
  for (int8_t x = 7; x >= -50; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Good Bye");
    matrix.writeDisplay();
    delay(100);
  }
}
