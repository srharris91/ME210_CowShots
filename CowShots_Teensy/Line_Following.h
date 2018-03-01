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


void Follow_Line(void) {

  //Read the IR LED measurements
  UpdateLineSensorValues();
  
  Sensor_1_Color = Get_Color(Sensor_1);
  Sensor_2_Color = Get_Color(Sensor_2);
  Sensor_3_Color = Get_Color(Sensor_3);

  
  //Apply saturation 
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
      //Serial.println("Something is wrong in applying saturation");
  }
  //Run the motor
  
  Advance();
  
}


