/*---------------Includes-----------------------------------*/
#include <AccelStepper.h>

/*---------------Module Variables---------------------------*/
AccelStepper stepmotor(1, 3, 4); // pin 3 = step, pin 4 = direction
int distance = 10;

void Setup_Stepper(void) {
  stepmotor.setMaxSpeed(2000);
}

void runmotor(void) {
  mystepper.move(distance);
}

