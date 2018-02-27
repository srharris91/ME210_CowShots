/* 
 * Functions to be used for following the Line, this needs functions from Line_Sensing.h
 * But we don't need an extra include here. 
*/

//Sensor 1 is on the left, sensor 2 is on the right

// ------------------ VARIABLES ----------------------- //
double previous_error = 0; //For the D of PID
double cumulated_error=0; //For the I of PID

double Kp = 5.; //Gains
double Kd = 0.;
double Ki = 0.0;

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
  Sensor_1 = Get_Color(Sensor_1);
  Sensor_2 = Get_Color(Sensor_2);
  Sensor_3 = Get_Color(Sensor_3);
  
  //Update error terms
  previous_error = error;
  error = Sensor_2 - Sensor_3; //will be positive if we are going too far right
  
  cumulated_error += error;

  //Correction
  correction = Kp*(error + Ki*cumulated_error + Kd*(error - previous_error));
  Serial.println(correction);
  //Anti windup
  if(correction > 25) { //We could tune that
    correction = 25 ;
    cumulated_error -= error;
  }
  else if(correction < -25) {
    correction = -25;
    cumulated_error = -error;
  }

  //Update right and left motor speeds
  Right_Speed = DutyCycle + correction;
  Left_Speed = DutyCycle - correction;
  
  //Apply saturation 
  if (Right_Speed < 0) {
    Right_Speed = -Right_Speed;
    Right_Direction = HIGH;
  }
  else {
    Right_Direction = LOW;
  }
  
  if (Right_Speed > Max_Speed) {
    Right_Speed = Max_Speed;
  }
  
  if (Left_Speed > Max_Speed) {
    Left_Speed = Max_Speed;
  }

  if (Left_Speed < 0) {
    Left_Speed = -Left_Speed;
    Left_Direction = HIGH;
  }
  else {
    Left_Direction = LOW;
  }

  //Run the motor
  Advance();
  
}
