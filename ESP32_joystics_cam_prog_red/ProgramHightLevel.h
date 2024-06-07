#pragma once

#include <Arduino.h>
#include "ARA_ESP.h"

class ProgramHightLevel
{
  public:
    void TakeOff(float height);
    void TurnRight(float angle);
    void TurnLeft(float angle);
    void Landing();
    void main_f();

  private:
  uint16_t ROLL;
  uint16_t PITCH;
  float YAW;
  float THROTTLE;
  uint16_t AUX1;
  uint16_t AUX2;
  uint16_t AUX3;
  uint16_t AUX4;
  //bool button;
};

extern ProgramHightLevel program;
