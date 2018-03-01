/*---------------Module Variables---------------------------*/
AccelStepper stepmotor(1, 3, 4); // pin 3 = step, pin 4 = direction
int distance = 10;

void Setup_Stepper(void) {
    stepmotor.setMaxSpeed(40);
}

void Move_Stepper_Motor(void) {
    stepmotor.move(distance);
}
void Run_Stepper_Motor(){
    stepmotor.run();
}

