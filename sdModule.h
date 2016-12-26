/*
  sdModule.h - Library for sd logging module.
  Created by Can Bagdiken, November 20, 2016.
  Released into the public domain.
*/
#ifndef sdModule_h
#define sdModule_h


#include "Arduino.h"

class sdModule
{

  public:
    sdModule(int pin);
    void init();
    int findLastGroup();
    int findLastFile();
    bool setErrorPin(int data);
    bool addInfo(String key, String val);
    bool add(String data);
    void setError(String errorMsg);
    int checkSize();
    bool setFileSizeLimit(int data);
    bool setTourLimit(int data);
  private:
    int _pin;
    unsigned long _fileSizeLimit;
    int _lastGroup;
    unsigned long _lastFileSize;
    int _lastFile;
    int _checkTour;
    int _tourLimit;
    int _errorPin;
};

#endif
