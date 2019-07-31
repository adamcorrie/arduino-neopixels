#include <Adafruit_NeoPixel.h>

#define pixelsPin 6
#define buttonPin 7

const int numberOfPixels = 16;

Adafruit_NeoPixel pixelsStrip(numberOfPixels, pixelsPin, NEO_GRB + NEO_KHZ800);
enum trafficLightMode {
  RED,
  AMBER,
  GREEN
};
trafficLightMode currentMode;
int previousButtonState;
bool buttonPressed;

void setup() {
  currentMode = GREEN;
  previousButtonState = LOW;
  buttonPressed = false;
  pixelsStrip.begin();
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);
  if ((previousButtonState == LOW) && (currentButtonState == HIGH)) {
    buttonPressed = true;
    delay(50); 
  }
  // store current button state for next cycle
  previousButtonState = currentButtonState;
  pixelsStrip.clear();
  switch(currentMode) {
    case RED:
    pixelsStrip.setPixelColor(0, pixelsStrip.Color(0, 0, 0));
    pixelsStrip.setPixelColor(1, pixelsStrip.Color(0, 0, 0));
    pixelsStrip.setPixelColor(2, pixelsStrip.Color(255, 0, 0));
    if (buttonPressed) {
      currentMode = GREEN;
      buttonPressed = false;
    }
    break;
    case AMBER:
    pixelsStrip.setPixelColor(0, pixelsStrip.Color(0, 0, 0));
    pixelsStrip.setPixelColor(1, pixelsStrip.Color(255, 191, 0));
    pixelsStrip.setPixelColor(2, pixelsStrip.Color(0, 0, 0));
    if (buttonPressed) {
      currentMode = RED;
      buttonPressed = false;
    }
    break;
    case GREEN:pixelsStrip.setPixelColor(0, pixelsStrip.Color(0, 255, 0));
    pixelsStrip.setPixelColor(1, pixelsStrip.Color(0, 0, 0));
    pixelsStrip.setPixelColor(2, pixelsStrip.Color(0, 0, 0));
    if (buttonPressed) {
      currentMode = AMBER;
      buttonPressed = false;
    }
    break;
  }
  pixelsStrip.show();
}
