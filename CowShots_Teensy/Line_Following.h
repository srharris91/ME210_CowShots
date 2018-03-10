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
double correction_saturation=40.;

double Kp = 0.07; //Gains
double Kd = 1.7;
double Ki = 0.00;

typedef enum {
    LEFT, RIGHT
} turn;
turn turn_Remember;


//In case we hit a gray or black turning tape we want to stop following line with an interrupt, using this for example
bool Breaking_Event = 0;
// ---------------------------------------------------- //

//Module Functions
void Follow_Line(void);
void Follow_Line_PID(void);
void Follow_Line_Backwards_PID(void);
void Reset_PID_vars(void);

// ------------------- TIMER -------------------------- //
// Timer we will use to read IR values and update motor speeds with PID
IntervalTimer Line_Sampling_Timer;
IntervalTimer Reset_PID_vars_Timer;
int sampling_rate = 1; //in ms
// ---------------------------------------------------- //


// -------------------------- SETUP FUNCTIONS ---------------------------- //
void Setup_Line_Following(void) {
   Line_Sampling_Timer.begin(Follow_Line, 10*sampling_rate); //10 micro
}
void Setup_Line_Following_PID(void) {
   Line_Sampling_Timer.begin(Follow_Line_PID, 5000*sampling_rate);
   //Reset_PID_vars_Timer.begin(Reset_PID_vars, 300000);
   previous_error = save_previous_error; //For the D of PID
   cumulated_error = 0; //For the I of PID
}
void Setup_Line_Following_Backwards_PID(void) {
   Line_Sampling_Timer.begin(Follow_Line_Backwards_PID, 5000*sampling_rate);
   //Reset_PID_vars_Timer.begin(Reset_PID_vars, 300000);
   previous_error = save_previous_error; //For the D of PID
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
void Stop_Line_Following_Backwards_PID(void) {
  Line_Sampling_Timer.end();
  Reset_PID_vars_Timer.end();
  previous_error = 0; //For the D of PID
  cumulated_error = 0; //For the I of PID
}
// ----------------------------------------------------------------------- //


void Follow_Line_PID(void) {

  //Read the IR LED measurements
  UpdateLineSensorValues();
  
  //Sensor_1_Color = Get_Color1(Sensor_1);
  //Sensor_2_Color = Get_Color(Sensor_2);
  //Sensor_3_Color = Get_Color(Sensor_3);

  //Error calculation
  previous_error = error;
  //error = Sensor_2_Color - Sensor_3_Color; //error is big if we are too far right, so we measure black on left (3) and white on right (2)
  error=(float(Sensor_2)-float(Sensor_3));
  if (error > 0) {
    error *=1.5;
  }
  cumulated_error += error;

  //Saturation on cumulated error
  if (cumulated_error*Ki > 10) {
    cumulated_error = 10./Ki;
  }
  else if (cumulated_error*Ki < -10) {
    cumulated_error = -10./Ki;
  }

  //Correction calculation
  correction = Kp*error + Ki*cumulated_error + Kd*(error-previous_error);

  //Saturation on correction
  if (correction > correction_saturation) {
    correction = correction_saturation;
  }
  else if (correction < -correction_saturation) {
    correction = -correction_saturation;
  }

  //Instead of keeping constant speed we will rather set the speeds slower:

  if (correction > 0) { //We want to turn left
    Right_Speed = DutyCycle + correction/2.;
    Left_Speed = DutyCycle - correction/2.;
    Right_Direction = LOW;
    Left_Direction = LOW;
    
    //Set the directions in case left
    if (Left_Speed < 0) {
      Left_Speed = DutyCycle-correction;
      Left_Direction = HIGH;
    }
    
  }
  else {
    Left_Speed = DutyCycle - correction/2.;
    Right_Speed = DutyCycle + correction/2.;
    Right_Direction = LOW;
    Left_Direction = LOW;

    if (Right_Speed < 0) {
      Right_Speed = -Right_Speed;
      Right_Direction = HIGH;
    }
  }
  //Serial.println(Right_Speed);
  //Serial.println(correction);
  Advance();
  
}


void Follow_Line(void) {
  int change_dutyCycle=10;
  //Read the IR LED measurements
  UpdateLineSensorValues();
  
  Sensor_1_Color = Get_Color1(Sensor_1);
  Sensor_2_Color = Get_Color(Sensor_2);
  Sensor_3_Color = Get_Color(Sensor_3);

  
  //Apply saturation 
  if (Sensor_2_Color == 2 && Sensor_3_Color == 2) {
    if (turn_Remember == RIGHT){
        Right_Speed = DutyCycle-change_dutyCycle;
        Left_Speed = DutyCycle;
    }
    else if (turn_Remember == LEFT){
        Right_Speed = DutyCycle;
        Left_Speed = DutyCycle - change_dutyCycle;
    }
    //Right_Speed = DutyCycle;
    //Left_Speed = DutyCycle;
    //Serial.println(0);
  } else if (Sensor_2_Color == 0){
    Right_Speed = DutyCycle - change_dutyCycle;
    Left_Speed = DutyCycle;
    turn_Remember=RIGHT;
    //Serial.println(1);
  } else if (Sensor_3_Color == 0){
    Right_Speed = DutyCycle;
    Left_Speed = DutyCycle - change_dutyCycle;
    turn_Remember=LEFT;
    //Serial.println(2);
  }
  else{
      //Serial.println("Something is wrong in applying saturation");
  }
  //Run the motor

  save_previous_error = previous_error;
  
  Advance();
  
}

void Reset_PID_vars(void) {
  cumulated_error = 0;
  previous_error = 0;
}


void Follow_Line_Backwards_PID(void) {

  //Read the IR LED measurements
  UpdateLineSensorValues();
  

  //Error calculation
  previous_error = error;
  //error = Sensor_2_Color - Sensor_3_Color; //error is big if we are too far right, so we measure black on left (3) and white on right (2)
  error= -1.0*(float(Sensor_2)-float(Sensor_3));
  if (error < 0) {
    error *=1.5;
  }
  cumulated_error += error;

  //Saturation on cumulated error
  if (cumulated_error*Ki > 10) {
    cumulated_error = 10./Ki;
  }
  else if (cumulated_error*Ki < -10) {
    cumulated_error = -10./Ki;
  }

  //Correction calculation
  correction = Kp*error + Ki*cumulated_error + Kd*(error-previous_error);

  //Saturation on correction
  if (correction > correction_saturation) {
    correction = correction_saturation;
  }
  else if (correction < -correction_saturation) {
    correction = -correction_saturation;
  }

  //Instead of keeping constant speed we will rather set the speeds slower:

  if (correction > 0) { //We want to turn left
    Right_Speed = DutyCycle + correction/2.;
    Left_Speed = DutyCycle - correction/2.;
    Right_Direction = LOW;
    Left_Direction = LOW;
    
    //Set the directions in case left
    if (Left_Speed < 0) {
      Left_Speed = DutyCycle-correction;
      Left_Direction = HIGH;
    }
    
  }
  else {
    Left_Speed = DutyCycle - correction/2.;
    Right_Speed = DutyCycle + correction/2.;
    Right_Direction = LOW;
    Left_Direction = LOW;

    if (Right_Speed < 0) {
      Right_Speed = -Right_Speed;
      Right_Direction = HIGH;
    }
  }

  Advance();
  
}

