#pragma once

#include "Pin.hpp"

class LED {
public:
  void toggle();
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
  virtual void setOn(bool isOn) = 0;
  bool isOn();
protected:
  bool mIsOn = false;
};

inline void LED::toggle() {
  if (isOn())
    turnOff();
  else
    turnOn();
}

inline bool LED::isOn() {
  return mIsOn;
}

class DigitalLED : DigitalPin, public LED {
public:
  DigitalLED(int pinId) : DigitalPin(pinId, DigitalPin::Mode::Output) {}
  ~DigitalLED() = default;

  void turnOn() override;
  void turnOff() override;
  void setOn(bool isOn) override;
};

inline void DigitalLED::turnOn() {
  digitalWrite(getId(), HIGH);
}

inline void DigitalLED::turnOff() {
  digitalWrite(getId(), LOW);
}

inline void DigitalLED::setOn(bool isOn) {
  digitalWrite(getId(), isOn ? HIGH : LOW);
}

class AnalogLED : AnalogPin, public LED {
public:
  AnalogLED(int pinId) : AnalogPin(pinId, AnalogPin::Mode::Output) {}
  ~AnalogLED() = default;

  void turnOn() override;
  void turnOff() override;
  void setOn(bool isOn) override;
};

inline void AnalogLED::turnOn() {
  analogWrite(getId(), HIGH);
}

inline void AnalogLED::turnOff() {
  analogWrite(getId(), LOW);
}

inline void AnalogLED::setOn(bool isOn) {
  analogWrite(getId(), isOn ? HIGH : LOW);
}
