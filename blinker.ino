#include "PinLib/Pin.hpp"
#include "PinLib/LED.hpp"
#include "PinLib/Button.hpp"
#include "PinLib/Timer.hpp"

#define OUT_GREEN 11
#define OUT_YELLOW 12
#define OUT_RED 13

#define IN_BUTTON 8

#define BLINK_TIME 125

enum LedMode {
  G_ON = 0,
  RY_SYM_1 = 1,
  RY_ALT_1 = 2,
  RY_ALT_2 = 3,
};

void redCallback();
void yellowCallback();
void blinkCallback();

PushButton button(IN_BUTTON);
DigitalLED green(OUT_GREEN);
DigitalLED yellow(OUT_YELLOW);
DigitalLED red(OUT_RED);

Timer redTimer(1000000, redCallback, true);
Timer yellowTimer(1000000, yellowCallback, true);
Timer blinkTimer(BLINK_TIME, blinkCallback, true, true);

void setup() {
  Serial.begin(9600);
}




int mode = 0;

bool isBlinkOn = true;
bool isOnY = true;
bool isOnR = true;

void redCallback() {
  isOnR = !isOnR;
}

void yellowCallback() {
  isOnY = !isOnY;
}

void blinkCallback() {
  isBlinkOn = !isBlinkOn;
}

void runMode1() {
    redTimer.stop();
    yellowTimer.stop();
    green.turnOn();
    yellow.turnOff();
    red.turnOff();
}

void runMode2() {
    green.turnOff();
    yellow.setOn(isOnY && isBlinkOn);
    red.setOn(isOnR && isBlinkOn);
    redTimer.setInterval(1000);
    yellowTimer.setInterval(1000);
}

void runMode3() {
    green.turnOff();
    yellow.setOn(isOnY && isBlinkOn);
    red.setOn(!isOnY && isBlinkOn);
    redTimer.setInterval(2000);
    yellowTimer.setInterval(2000);
}

void runMode4() {
    green.turnOff();
    yellow.setOn(isOnY && isBlinkOn);
    red.setOn(isOnR && isBlinkOn);
    redTimer.setInterval(500);
    yellowTimer.setInterval(2000);
}

const void (*modeFunctions[4])() = {runMode1, runMode2, runMode3, runMode4 };


void update() {
  button.update();
  redTimer.update();
  yellowTimer.update();
  blinkTimer.update();
}

void loop() {
  update();

  if (button.isPressed()) {
    mode = (mode + 1) % 4;
    isBlinkOn = true;
    isOnY = true;
    isOnR = true;
    redTimer.start();
    yellowTimer.start();
    blinkTimer.start();
  }

  modeFunctions[mode]();
}
