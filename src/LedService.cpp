#include "LedService.h"

LedService::LedService(int redPin, int greenPin, int bluePin)
{
    _redPin = redPin;
    _greenPin = greenPin;
    _bluePin = bluePin;
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

void LedService::TurnOff()
{
    digitalWrite(_redPin, LOW);
    digitalWrite(_greenPin, LOW);
    digitalWrite(_bluePin, LOW);
}

void LedService::SetColor(Color color)
{
    switch(color) 
    {
        case Color::Red :
            digitalWrite(_redPin, HIGH);
            digitalWrite(_greenPin, LOW);
            digitalWrite(_bluePin, LOW);
            break; 
        case Color::Green :
            digitalWrite(_redPin, HIGH);
            digitalWrite(_greenPin, LOW);
            digitalWrite(_bluePin, LOW);
            break; 
        case Color::Blue :
            digitalWrite(_redPin, LOW);
            digitalWrite(_greenPin, LOW);
            digitalWrite(_bluePin, HIGH);
            break; 
        case Color::Yellow :
            digitalWrite(_redPin, HIGH);
            digitalWrite(_greenPin, HIGH);
            digitalWrite(_bluePin, LOW);
            break; 
    }
}