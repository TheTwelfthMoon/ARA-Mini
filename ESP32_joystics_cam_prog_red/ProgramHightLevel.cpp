#include <iterator>
#include <Arduino.h>
#include "ARA_ESP.h"
#include "ProgramHightLevel.h"

//ARA_ESP esp = ARA_ESP();
extern int button;
float curr_height = -1;
ProgramHightLevel program = ProgramHightLevel();

void ProgramHightLevel::main_f(){
  esp.throttle(THROTTLE);
  esp.yaw(YAW);
  
}

void ProgramHightLevel::TakeOff(float height)
{
    if (height < 0 || height > 1)
        return;
    
    curr_height = 0;
    float delta = height / 250;

    esp.nav_mode(2);
    for(int i = 0; i < 250; i++)
    {
        curr_height += delta;
        THROTTLE = curr_height;

        main_f();
        delay(20);
    }

}

/// @brief
/// @param angle в градусах
void ProgramHightLevel::TurnRight(float angle)
{
    float old_max = 2000;
    float old_min = 1500;
    float new_max = 400;
    float new_min = 0;

    float old_range = old_max-old_min;
    float new_range = new_max-new_min;

    unsigned long recalc = angle /abs((((1600 - old_min) * new_range) / old_range) + new_min);

    float old_max_y = 1800;
    float old_min_y = 1200;
    float new_max_y = 1;
    float new_min_y = -1;

    float old_range_y = old_max_y-old_min_y;
    float new_range_y = new_max_y-new_min_y;
    for (int i = 0; i < recalc*100; i++) {
      YAW = (((1600 - old_min_y) * new_range_y) / old_range_y) + new_min_y;
      
      main_f();
      delay(20);
    }
    YAW = 0;

    delay(20);
    main_f();
}

/// @brief
/// @param angle в градусах
void ProgramHightLevel::TurnLeft(float angle)
{
    float old_max = 2000;
    float old_min = 1500;
    float new_max = 400;
    float new_min = 0;

    float old_range = old_max-old_min;
    float new_range = new_max-new_min;

    unsigned long recalc = angle /abs((((1400 - old_min) * new_range) / old_range) + new_min);

    float old_max_y = 1800;
    float old_min_y = 1200;
    float new_max_y = 1;
    float new_min_y = -1;

    float old_range_y = old_max_y-old_min_y;
    float new_range_y = new_max_y-new_min_y; 
    for (int i = 0; i < 300; i++) {
      YAW = (((1400 - old_min_y) * new_range_y) / old_range_y) + new_min_y;
      delay(20);
      main_f();
    }
    YAW = 0;
    delay(20);
    main_f();
}

void ProgramHightLevel::Landing()
{
    float delta = curr_height / 250;
    for(int i = 0; i < 250; i++)
    {
        float old_max = 1;
        float old_min = 0;
        float new_max = 1;
        float new_min = 0;
        curr_height -= delta;

        THROTTLE = curr_height;
        main_f();        
        delay(20);
    }
    
    esp.nav_mode(1);
    curr_height = 0;
    esp.throttle(0);
}