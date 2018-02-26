#include <IntervalTimer.h>
#include "Motor.h"
#include "Line_Sensing.h"

//Sensor 1 is on the left, sensor 2 is on the right

// ------------------ VARIABLES ----------------------- //
int error=0;
int previous_error = 0; //For the D of PID
long cumulated_error=0; //For the I of PID

unsigned int Kp = 1; //Gains
unsigned int Kd = 2;
unsigned int Ki = 1;
int correction = 0; //This will be our resulting PID correction

//In case we hit a gray or black turning tape we want to stop following line with an interrupt, using this for example
bool Breaking_Event = 0;
// ---------------------------------------------------- //

//Module Functions
void Follow_Line(void);

// ------------------- TIMER -------------------------- //
// Timer we will use to read IR values and update motor speeds with PID
IntervalTimer Line_Sampling_Timer;
int sampling_rate = 10; //in ms
// ---------------------------------------------------- //


// -------------------------- SETUP FUNCTIONS ---------------------------- //
void Setup_Line_Following(void) {
   Line_Sampling_Timer.begin(Follow_Line, 1000*sampling_rate);
}
// ----------------------------------------------------------------------- //

//To use when we transition between states so that we don't mess up the variables
void Reset_PID_vars(void) {
  error = 0;
  cumulated_error = 0;
}

void Follow_Line(void) {

  //Read the IR LED measurements
  UpdateLineSensorValues();
  
  //Set flag if we found a gray line so that we could use an interrupt to transition to a new state
  if ( Get_Color(Sensor_3) != 2) {
    Breaking_Event = 1;
  }
  
  //Update error terms
  previous_error = error;
  error = Sensor_2 - Sensor_1; //will be positive if we are going too far right
  cumulated_error += error;

  //Correction
  correction = Kp*(error + Ki*cumulated_error + Kd*(error - previous_error));
  
  //Anti windup
  if(correction > 75) { //We could tune that
    correction = 75;
    cumulated_error -= error;
  }
  else if(correction < 0) {
    correction = 0;
    cumulated_error = -error;
  }

  //Update right and left motor speeds
  Right_Speed = DutyCycle + correction;
  Left_Speed = DutyCycle - correction;

  //Apply saturation 
  if (Right_Speed < 0) {
    Right_Speed = -Right_Speed;
    Right_Direction = LOW;
  }
  else {
    Right_Direction = HIGH;
  }
  
  if (Right_Speed > Max_Speed) {
    Right_Speed = Max_Speed;
  }
  
    if (Left_Speed > Max_Speed) {
    Left_Speed = Max_Speed;
  }

  if (Left_Speed < 0) {
    Left_Speed = -Left_Speed;
    Left_Direction = LOW;
  }
  else {
    Left_Direction = HIGH;
  }

  //Run the motor
  Advance();
  
}

