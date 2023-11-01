#include "Pin.hpp"

#define OUT_GREEN 11
#define OUT_YELLOW 12
#define OUT_RED 13

#define IN_BUTTON 8

#define BLINK_TIME 125

DigitalPin button(IN_BUTTON, DigitalPin::Mode::InputPullUp);

void setup() {
  pinMode(OUT_GREEN, OUTPUT);
  pinMode(OUT_YELLOW, OUTPUT);
  pinMode(OUT_RED, OUTPUT);

  Serial.begin(9600);
}



bool isPressed = false;
bool isChanged = false;

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
  bool state = (bool) !button.read();
  isChanged = isPressed != state;
  isPressed = state;

  if (isChanged && isPressed){
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
    digitalWrite(OUT_GREEN, 1);
    digitalWrite(OUT_YELLOW, 0);
    digitalWrite(OUT_RED, 0);
    switchTimeR = 10000;
    switchTimeY = 10000;
  } else if (mode == RY_SYM_1) {
    digitalWrite(OUT_GREEN, 0);
    digitalWrite(OUT_YELLOW, !isOnY && isBlinkOn);
    digitalWrite(OUT_RED, !isOnR && isBlinkOn);
    switchTimeR = 1000;
    switchTimeY = 1000;
  } else if (mode == RY_ALT_1) {
    digitalWrite(OUT_GREEN, 0);
    digitalWrite(OUT_YELLOW, isOnY && isBlinkOn);
    digitalWrite(OUT_RED, !isOnY && isBlinkOn);
    switchTimeR = 2000;
    switchTimeY = 2000;
  } else if (mode == RY_ALT_2) {
    digitalWrite(OUT_GREEN, 0);
    digitalWrite(OUT_YELLOW, isOnY && isBlinkOn);
    digitalWrite(OUT_RED, isOnR && isBlinkOn);
    switchTimeR = 500;
    switchTimeY = 2000;
  }
}

