//NeoPixel에 달린 LED를 각각 주어진 인자값 색으로 채워나가는 함수
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//하나씩만 밝기를 키워줘서 움직여주는 함수
void pointMoving(uint32_t c, uint8_t wait, uint8_t b1, uint8_t b2) {

  //strip.setBrightness(b);
  //colorWipe(mainColor, 50);
  for (int i = 0; i < strip.numPixels(); i++) {

    //strip.setPixelColor(i, 70, 255, 255, b2);

    for (int j = 0; j < strip.numPixels(); j++) {
      if (j != i)
      {
        strip.setPixelColor(i, 70, 255, 255, b2);
        strip.setPixelColor(j, 70, 0, 255, b1);
      }
    }
    strip.show();
    delay(wait);
  }
  //  for (uint16_t i = 0; i < strip.numPixels(); i++) {
  //    strip.setPixelColor(i, c);
  //    strip.show();
  //    delay(wait);
  //
  //    //    strip.setPixelColor(i, c);
  //    //    strip.setBrightness(b1);
  //    //    strip.show();
  //    //    delay(wait);
  //  }
}

//모든 LED를 출력가능한 모든색으로 한번씩 보여주는 동작을 한번하는 함수
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//NeoPixel에 달린 LED를 각각 다른색으로 시작하여 다양한색으로 5번 반복한다
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void whole(uint32_t c, uint8_t wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}


//255가지의 색을 나타내는 함수
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
