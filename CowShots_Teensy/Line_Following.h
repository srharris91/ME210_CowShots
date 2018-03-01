/* 
 * Functions to be used for following the Line, this needs functions from Line_Sensing.h
 * But we don't need an extra include here. 
*/

//Sensor 1 is on the left, sensor 2 is on the right

// ------------------ VARIABLES ----------------------- //
double previous_error = 0; //For the D of PID
double cumulated_error=0; //For the I of PID
double error = 0;
double correction = 0;

double Kp = 5.; //Gains
double Kd = 0.;
double Ki = 0.0;

//In case we hit a gray or black turning tape we want to stop following line with an interrupt, using this for example
bool Breaking_Event = 0;
// ---------------------------------------------------- //

//Module Functions
void Follow_Line(void);
void Follow_Line_PID(void);
void Reset_PID_vars(void);

// ------------------- TIMER -------------------------- //
// Timer we will use to read IR values and update motor speeds with PID
IntervalTimer Line_Sampling_Timer;
IntervalTimer Reset_PID_vars_Timer
int sampling_rate = 10; //in ms
// ---------------------------------------------------- //


// -------------------------- SETUP FUNCTIONS ---------------------------- //
void Setup_Line_Following(void) {
   Line_Sampling_Timer.begin(Follow_Line, 1000*sampling_rate);
}
void Setup_Line_Following_PID(void) {
   Line_Sampling_Timer.begin(Follow_Line_PID, 1000*sampling_rate);
   Reset_PID_vars_Timer.begin(Reset_PID_vars, 1500000);
   previous_error = 0; //For the D of PID
   cumulated_error = 0; //For the I of PID
}
// ----------------------------------------------------------------------- //

// -------------------------- END FUNCTIONS ---------------------------- //
void Stop_Line_Following(void) {
  Line_Sampling_Timer.end();
}
void Stop_Line_Following_PID(void) {
  Line_Sampling_Timer.end();
  Reset_PID_vars_Timer.end();
  previous_error = 0; //For the D of PID
  cumulated_error = 0; //For the I of PID
}
// ----------------------------------------------------------------------- //


void Follow_Line_PID(void) {

  //Read the IR LED measurements
  UpdateLineSensorValues();
  
  Sensor_1_Color = Get_Color(Sensor_1);
  Sensor_2_Color = Get_Color(Sensor_2);
  Sensor_3_Color = Get_Color(Sensor_3);

  //Error calculation
  previous_error = error;
  error = Sensor_2_Color - Sensor_3_Color; //error is big if we are too far right, so we measure black on left (3) and white on right (2)
  cumulated error += error;

  //Saturation on cumulated error
  if (cumulated_error > 25) {
    cumulated_error = 25;
  }
  else if (cumulated_error < -25) {
    cumulated_error = -25
  }

  //Correction calculation
  correction = Kp*error + Ki*cumulated_error + Kd*(error-previous_error);

  //Saturation on correction
  if (correction > 100) {
    correction = 100;
  }
  else if (correction < -100) {
    correction = -100
  }

  //Instead of keeping constant speed we will rather set the speeds slower:

  if (correction > 0) { //We want to turn left
    Right_Speed = DutyCycle;
    Left_Speed = DutyCycle - correction;
    Right_Direction = HIGH;
    Left_Direction = HIGH;
    
    //Set the directions in case left
    if (Left_Speed < 0) {
      Left_Speed = -Left_Speed;
      Left_Direction = LOW;
    }
    
  }
  else {
    Left_Speed = DutyCycle;
    Right_Speed = DutyCycle - correction
    Right_Direction = HIGH;
    Left_Direction = HIGH;

    if (Right_Speed < 0) {
      Right_Speed = -Right_Speed;
      Right_Direction ) LOW;
    }
  }
  
  Advance();
  
}


void Follow_Line(void) {

  //Read the IR LED measurements
  UpdateLineSensorValues();
  
  Sensor_1_Color = Get_Color(Sensor_1);
  Sensor_2_Color = Get_Color(Sensor_2);
  Sensor_3_Color = Get_Color(Sensor_3);

  
  //Apply saturation 
  error = Sensor_2_Color - Sensor_3_Color;
  correction = Kp*error + Ki*
  if (Sensor_2_Color == 2 && Sensor_3_Color == 2) {
    Right_Speed = DutyCycle;
    Left_Speed = DutyCycle;
    //Serial.println(0);
  } else if (Sensor_2_Color == 0){
    Right_Speed = 0;
    Left_Speed = DutyCycle;
    //Serial.println(1);
  } else if (Sensor_3_Color == 0){
    Right_Speed = DutyCycle;
    Left_Speed = 0;
    //Serial.println(2);
  }
  else{
      Serial.println("Something is wrong in applying saturation");
  }
  //Run the motor
  
  Advance();
  
}

void Reset_PID_vars(void) {
  cumulated_error = 0;
  previous_error = 0;
}

