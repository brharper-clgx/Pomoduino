#include "Arduino.h"
#include "LedService.h"

/**
 * CONSTANTS: 
 */
const long SECONDS = 1000;
const long MINUTES = 60 * SECONDS;
const long pomodoroDuration = 25 * MINUTES;
const long warningDuration = pomodoroDuration - 5 * MINUTES;

const int redLED = A0;
const int blueLED = A1;
const int greenLED = A2;
const int startButton = 2;
const int cancelButton = 3;
const int buzzer = 9;


/**
 * Local Variables: 
 */
volatile long startTime = -1;
volatile bool runEndSequence = false;
volatile bool fiveMinuteMark = false;

LedService ledService(redLED, greenLED, blueLED);


/**
 * Local methods
  */
bool timerHasExpired()
{
  if(startTime >= 0)
  {
    return (millis() - startTime) >= pomodoroDuration;
  }
  else
  {
    return false;
  }
}

bool pastFiveMinuteMark()
{
  if(startTime >= 0)
  {
    return (millis() - startTime) >= warningDuration;
  }
  else
  {
    return false;
  }
}

void updateState()
{
  if( timerHasExpired() )
  {
    runEndSequence = true;
    startTime = -1;
  }
  else if( pastFiveMinuteMark() )
  {
    fiveMinuteMark = true;
  }
}

void playSong()
{
    tone(buzzer, 1047);
    delay(400);
    tone(buzzer, 1175);
    delay(200);
    tone(buzzer, 785);
    delay(400);
    noTone(buzzer);
}

void endSequence()
{
  ledService.SetColor(Color::Blue);
  playSong();
  runEndSequence = false;
}

/**
 * INTERUPTS
 */
void onStart()
{
  startTime = millis();
  ledService.SetColor(Color::Red);
}

void onCancel()
{
  runEndSequence = true;
  startTime = -1;
}

/**
 * MAIN LOOP
  */
void setup()
{

  pinMode(startButton, INPUT);
  pinMode(buzzer, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(startButton), onStart, RISING);
  attachInterrupt(digitalPinToInterrupt(cancelButton), onCancel, RISING);

  ledService.SetColor(Color::Blue);
}

void loop()
{
  updateState();
  if(runEndSequence)
  {
    endSequence();
  }
  else if(fiveMinuteMark)
  {
    ledService.SetColor(Color::Yellow);
    fiveMinuteMark = false;
  }
}
