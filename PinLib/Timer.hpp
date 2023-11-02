#pragma once

class Timer {
public:
  Timer(unsigned long tickInterval, void (*callbackFunc)() = nullptr, bool repeat = false, bool start = false);
  Timer(unsigned long tickInterval, void (*callbackFunc)(void *userData), void *userData, bool repeat = false, bool start = false);
  ~Timer();

  void setRepeating(bool repeat);
  bool getRepeating();
  void setInterval(unsigned long interval);
  unsigned long getInterval();
  unsigned long getStartTime();
  unsigned long getStopTime();
  unsigned long getElapsedTime();
  unsigned long getLastTickTime();
  bool getIsRunning();
  void setCallback(void (*callbackFunc)());
  void setCallback(void (*callbackFunc)(void *userData));
  void setUserData(void *userData);

  void update();
  void start();
  void stop();
private:
  void init(bool start);

  unsigned long mInterval;
  unsigned long mStartTime;
  unsigned long mStopTime;
  unsigned long mLastTickTime;
  bool mShouldRepeat;
  bool mIsRunning;

  void (*mCallbackFunc)() = nullptr;
  void (*mCallbackFuncUD)(void *userData) = nullptr;
  void *mUserData = nullptr;
};
