/*
  sdModule.cpp - Library for sd logging module.
  Created by Can Bagdiken, November 20, 2016.
  Released into the public domain.
*/

#include "Arduino.h"
#include "sdModule.h"
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;


File myFile;
sdModule::sdModule(int pin){
  pinMode(pin, OUTPUT);
  _pin = pin;
  _checkTour = 0;
  _lastFileSize = 0;
  _lastGroup = 0;
  _lastFile = 0;
  _tourLimit = 100;
}

bool sdModule::setErrorPin(int data){
    if((data > 13) or (data < 0)){
        setError("ERROR PIN IS INCORRECT");
    }
    _errorPin = data;
    return true;
}



bool sdModule::setTourLimit(int data){
    if(data > 1000000){
        setError("Tour Value is too big!");
    }
    if(data < 1){
        setError("Tour Value is too small!");
    }
    _tourLimit = data;
    return true;
}

bool sdModule::setFileSizeLimit(int data){
    unsigned long maxLimit = 128; // MB
    maxLimit *= 1024;// MB to KB
    maxLimit *= 1024; // KB to BYTE
    data *= 1024; // KB to BYTE

    Serial.println(String(data) + " - " + String(maxLimit));
    if(data > (maxLimit)){
        setError("File Size Limit is too big!");
    }
    if(data < 100){
        setError("File Size Limit is too small!");
    }
    _fileSizeLimit = data;
    return true;
}

void sdModule::init(){
      if (!card.init(SPI_QUARTER_SPEED, _pin)) {
       setError("card.init");
     }

      if (!volume.init(card)) {
       setError("volume.init");
     }

      if (!SD.begin(_pin)) {
       setError("sd.begin");
     }

    _lastGroup = findLastGroup()+1;

    if (!SD.mkdir("/"+String(_lastGroup))) {
       setError("CREATE GROUP PROBLEM!!");
    }

    File SDtmpFile = SD.open("/"+String(_lastGroup));
     if (!SDtmpFile) {
       setError("OPEN GROUP PROBLEM!!");
    }
    SDtmpFile.close();
    _lastFile = 0;
}





bool sdModule::addInfo(String key,String val){
    File SDtmpFile = SD.open("/"+String(_lastGroup)+"/groupInfo.txt", FILE_WRITE);
    SDtmpFile.println(String(key)+"="+String(val));
    SDtmpFile.close();
    return true;
}




bool sdModule::add(String data){
    _checkTour = _checkTour + 1;
    if(_checkTour > _tourLimit){
        int _lastFileSize = checkSize();
        if(_lastFileSize > _fileSizeLimit){
            _lastFile = _lastFile+1;

            //Serial.println("Current Last File = "+String(_lastFile));
        }
        _checkTour = 0;
    }

    File SDtmpFile = SD.open("/"+String(_lastGroup)+"/"+String(_lastFile)+".txt", FILE_WRITE);
    SDtmpFile.println(String(data));
    SDtmpFile.close();

}






int sdModule::checkSize(){
        File tmpFile = SD.open("/"+String(_lastGroup)+"/"+String(_lastFile)+".txt", FILE_READ);
        _lastFileSize = (String(tmpFile.size())).toInt();
        tmpFile.close();
        return _lastFileSize;
}






int sdModule::findLastGroup(){
  int lastGroup = 0;
  File SDtmpFile = SD.open("/");
  SDtmpFile.rewindDirectory();
  while (true)
  {
        File entry = SDtmpFile.openNextFile();
        if (!entry){
            SDtmpFile.close();
          return lastGroup;
        }

        if (entry.isDirectory())
        {
            String tmpName = entry.name();
            int tmpOrder = tmpName.toInt();
            if(tmpOrder > lastGroup){
               lastGroup = tmpOrder;
            }
            entry.close();
        }
  }
  return lastGroup;
}

















void sdModule::setError(String errorMsg) {
  Serial.print(errorMsg);
  Serial.flush();
  delay(250);


  while(true){
         digitalWrite(_errorPin,HIGH);
         delay(200);
         digitalWrite(_errorPin,LOW);
         delay(100);
  }
}
