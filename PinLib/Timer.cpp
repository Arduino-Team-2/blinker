#include "Timer.hpp"
#include <Arduino.h>

Timer::Timer(unsigned long tickInterval, void (*callbackFunc)(), bool repeat, bool start)
  : mInterval(tickInterval), mShouldRepeat(repeat), mCallbackFunc(callbackFunc) {
  init(start);
}

Timer::Timer(unsigned long tickInterval, void (*callbackFunc)(void *userData), void *userData, bool repeat, bool start)
  : mInterval(tickInterval), mShouldRepeat(repeat), mCallbackFuncUD(callbackFunc), mUserData(userData), mIsRunning(start) {
  init(start);
}

void Timer::init(bool start) {
  if (start)
    this->start();
}

Timer::~Timer() {

}

void Timer::setRepeating(bool repeat) {
  mShouldRepeat = repeat;
}

bool Timer::getRepeating() {
  return mShouldRepeat;
}

void Timer::setInterval(unsigned long interval) {
  mInterval = interval;
}

unsigned long Timer::getInterval() {
  return mInterval;
}

unsigned long Timer::getStartTime() {
  return mStartTime;
}

unsigned long Timer::getStopTime() {
  return mStopTime;
}

unsigned long Timer::getElapsedTime() {
  return mStopTime - mStartTime;
}

unsigned long Timer::getLastTickTime() {
  return mLastTickTime;
}

bool Timer::getIsRunning() {
  return mIsRunning;
}

void Timer::setCallback(void (*callbackFunc)()) {
  mCallbackFunc = callbackFunc;
}

void Timer::setCallback(void (*callbackFunc)(void *userData)) {
  mCallbackFuncUD = callbackFunc;
}

void Timer::setUserData(void *userData) {
  mUserData = userData;
}

void Timer::update() {
  if (!mIsRunning)
    return;
  unsigned long currentTime = millis();
  if (currentTime - mLastTickTime < mInterval)
    return;
  if (mCallbackFuncUD)
    mCallbackFuncUD(mUserData);
  if (mCallbackFunc)
    mCallbackFunc();
  if (mShouldRepeat)
    mLastTickTime = currentTime;
  else
    stop();
}

void Timer::start() {
  mStartTime = millis();
  mLastTickTime = mStartTime;
  mIsRunning = true;
  update();
}

void Timer::stop() {
  if (!mIsRunning)
    return;
  mStopTime = millis();
  mIsRunning = false;
}
