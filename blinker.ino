#include "PinLib/Pin.hpp"
#include "PinLib/LED.hpp"
#include "PinLib/Button.hpp"

#define OUT_GREEN 11
#define OUT_YELLOW 12
#define OUT_RED 13

#define IN_BUTTON 8

#define BLINK_TIME 125

PushButton button(IN_BUTTON);
DigitalLED green(OUT_GREEN);
DigitalLED yellow(OUT_YELLOW);
DigitalLED red(OUT_RED);

void setup() {
  Serial.begin(9600);
}



enum LedMode {
  G_ON = 0,
  RY_SYM_1 = 1,
  RY_ALT_1 = 2,
  RY_ALT_2 = 3,
};

int mode = 0;

unsigned long timeMs;
unsigned long lastBlink = 0;
unsigned long lastSwitchY = 0;
unsigned long lastSwitchR = 0;
unsigned long switchTimeY = 0;
unsigned long switchTimeR = 0;
bool isBlinkOn = true;
bool isOnY = true;
bool isOnR = true;

void loop() {
  timeMs = millis();
  button.update();

  if (button.isPressed()){
    mode = (mode + 1) % 4;
    lastSwitchY = 0;
    lastSwitchR = 0;
    lastBlink = 0;
    isBlinkOn = true;
    isOnY = true;
    isOnR = true;
  }

  if (timeMs - lastSwitchY > switchTimeY) {
    isOnY = !isOnY;
    lastSwitchY = timeMs;
  }
  if (timeMs - lastSwitchR > switchTimeR) {
    isOnR = !isOnR;
    lastSwitchR = timeMs;
  }
  if (timeMs - lastBlink > BLINK_TIME) {
    isBlinkOn = !isBlinkOn;
    lastBlink = timeMs;
  }

  if (mode == G_ON) {
    green.turnOn();
    yellow.turnOff();
    red.turnOff();
    switchTimeR = 10000;
    switchTimeY = 10000;
  } else if (mode == RY_SYM_1) {
    green.turnOff();
    yellow.setOn(!isOnY && isBlinkOn);
    red.setOn(!isOnR && isBlinkOn);
    switchTimeR = 1000;
    switchTimeY = 1000;
  } else if (mode == RY_ALT_1) {
    green.turnOff();
    yellow.setOn(isOnY && isBlinkOn);
    red.setOn(!isOnY && isBlinkOn);
    switchTimeR = 2000;
    switchTimeY = 2000;
  } else if (mode == RY_ALT_2) {
    green.turnOff();
    yellow.setOn(isOnY && isBlinkOn);
    red.setOn(isOnR && isBlinkOn);
    switchTimeR = 500;
    switchTimeY = 2000;
  }
}


