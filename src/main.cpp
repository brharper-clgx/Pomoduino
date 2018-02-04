#include "Arduino.h"
#include "LedService.h"

/**
 * GLOBAL: 
 */
const long SECONDS = 1000;
const long MINUTES = 60 * SECONDS;
const long pomodoroDuration = 2 * MINUTES;
const long warningDuration = 1 * MINUTES;

const int redLED = A0;
const int blueLED = A1;
const int greenLED = A2;
const int startButton = 2;
const int cancelButton = 3;
const int buzzer = 9;

volatile long pomodoroStart = -1;
volatile bool pomodoroIsRunning = false;
bool callBuzzer = false;

LedService ledService(redLED, greenLED, blueLED);

/**
 * INTERUPTS
 */
void onStart()
{
  pomodoroIsRunning = true;
  pomodoroStart = millis();
  ledService.SetColor(Color::Red);
  callBuzzer = true;
}

void onCancel()
{
  pomodoroIsRunning = false;
  ledService.SetColor(Color::Blue);
}

/**
 * Local methods
  */
bool pomodoroIsOver()
{
  return !pomodoroIsRunning || (millis() - pomodoroStart) >= pomodoroDuration;
}

bool fiveMinutesLeft()
{
  return (millis() - pomodoroStart) >= (pomodoroDuration - warningDuration);
}

void playSong()
{
  if (callBuzzer && pomodoroIsOver())
  {
    tone(buzzer, 1047); // Send 1KHz sound signal...
    delay(400);
    tone(buzzer, 1175);
    delay(200);
    tone(buzzer, 785);
    delay(400);
    noTone(buzzer);
    callBuzzer = false;
  }
}

/**
 * MAIN
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
  if (pomodoroIsOver())
  {
    ledService.SetColor(Color::Blue);
    playSong();
  }
  else if (fiveMinutesLeft())
  {
    ledService.SetColor(Color::Yellow);
  }
}
