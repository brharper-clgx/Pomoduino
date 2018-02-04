#ifndef LedService_h
#define LedService_h
#include "Arduino.h"

enum Color { Red, Green, Blue, Yellow };

class LedService
{
  public:
    LedService(int redPin, int greenPin, int bluePin);
    void TurnOff();
    void SetColor(Color color);
   
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
    
};

#endif