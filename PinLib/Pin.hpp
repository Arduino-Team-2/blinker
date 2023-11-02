#pragma once

#include <Arduino.h>

template<typename T>
class Pin {
public:
  enum class Mode {
      Input = INPUT,
      Output = OUTPUT,
      InputPullUp = INPUT_PULLUP
  };

  Pin(int pinId, Mode mode);
  ~Pin() = default;

  void setMode(Mode mode);
  int getId();

  virtual T read() = 0;
  virtual void write(T value) = 0;
protected:
    int mId;
    Mode mMode;
};

template<typename T>
Pin<T>::Pin(int pinId, Mode mode) : mId(pinId) {
    setMode(mode);
}

template<typename T>
inline int Pin<T>::getId() {
  return mId;
}

template<typename T>
inline void Pin<T>::setMode(Mode mode) {
    mMode = mode;
    pinMode(mId, static_cast<int>(mMode));
}

class DigitalPin : public Pin<int> {
public:
    DigitalPin(int pinId, Pin::Mode mode);
    ~DigitalPin() = default;

    int read() override;
    void write(int value) override;
};

DigitalPin::DigitalPin(int pinId, Pin::Mode mode) : Pin<int>(pinId, mode) {}

inline int DigitalPin::read() {
    return digitalRead(mId);
}

inline void DigitalPin::write(int value) {
    digitalWrite(mId, value);
}

class AnalogPin : public Pin<float> {
public:
    AnalogPin(int pinId, Pin::Mode mode);
    ~AnalogPin() = default;

    float read() override;
    void write(float value) override;
};

AnalogPin::AnalogPin(int pinId, Pin::Mode mode) : Pin<float>(pinId, mode) {}

inline float AnalogPin::read() {
    return analogRead(mId);
}

inline void AnalogPin::write(float value) {
    analogWrite(mId, value);
}


