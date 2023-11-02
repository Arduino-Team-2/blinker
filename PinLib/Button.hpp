#pragma once

#include "Pin.hpp"

class PushButton : DigitalPin {
public:
  PushButton(int pinId) : DigitalPin(pinId, DigitalPin::Mode::InputPullUp) {}
  ~PushButton() = default;

  void update();
  bool isPressed();
  bool isHeld();
  bool isDepressed();
private:
  bool mIsPressed = false;
  bool mIsChanged = false;
};

void PushButton::update() {
  bool state = (bool) !read();
  mIsChanged = mIsPressed != state;
  mIsPressed = state;
}

inline bool PushButton::isPressed() {
  return mIsPressed && mIsChanged;
}

inline bool PushButton::isHeld() {
  return mIsPressed && !mIsChanged;
}

inline bool PushButton::isDepressed() {
  return !mIsPressed && mIsChanged;
}
