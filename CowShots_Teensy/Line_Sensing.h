/*
 *Functions to be used for reading the IR sensors to follow the line.
 *This includes reading the analog input to the Teensy from the IR sensors
*/


//Sensor pins
int IR_SENSOR_READ_1 = 14;
int IR_SENSOR_READ_2 = 15;
int IR_SENSOR_READ_3 = 16;

// Sensor values, between 0 and 1024
unsigned int Sensor_1;
unsigned int Sensor_2;
unsigned int Sensor_3;



//Sensor Timer
IntervalTimer Line_Sampling_Timer_Print;
int sampling_rate_print = 500; //This is in ms so that we store it in smaller variable


// Some module function declarations here --------- //
void UpdateLineSensorValues(void);
void PrintLineSensorValues(void);
int Get_Color(int Sensor_Value);
int Get_Color1(int Sensor_Value);
// ------------------------------------------------ //


// --------------------- SETUP FUNCTIONS ------------------------ //
void Setup_Line_Sensors(void) {
  pinMode(IR_SENSOR_READ_1, INPUT);
  pinMode(IR_SENSOR_READ_2, INPUT);
  pinMode(IR_SENSOR_READ_3, INPUT);
}

void Setup_Line_Sampling_Print(void) {
   Line_Sampling_Timer_Print.begin(PrintLineSensorValues, 10000*sampling_rate_print);
}
void Setup_Line_Sampling(void) {
   Line_Sampling_Timer_Print.begin(UpdateLineSensorValues, 10*sampling_rate_print);
}

void Stop_Line_Sampling(void) {
   Line_Sampling_Timer_Print.end();
}
// --------------------------------------------------------------- //


// ------------------ Read sensor values ------------------------- //
void Read_IR_Sensor_1(void) {
  Sensor_1 = analogRead(IR_SENSOR_READ_1);
  Sensor_1_Color = Get_Color1(Sensor_1);
  
}
void Read_IR_Sensor_2(void) {
  Sensor_2 = analogRead(IR_SENSOR_READ_2);
  Sensor_2_Color = Get_Color(Sensor_2);
}
void Read_IR_Sensor_3(void) {
  Sensor_3 = analogRead(IR_SENSOR_READ_3);
  Sensor_3_Color = Get_Color(Sensor_3);
}
// --------------------------------------------------------------- //


void PrintLineSensorValues(void) {
  Read_IR_Sensor_1();
  Read_IR_Sensor_2();
  Read_IR_Sensor_3();
  Serial.println( "------------ LINE SENSING ----------------");
  Serial.print("Sensor 1 Value: ");
  Serial.println(Sensor_1);
  Serial.print("Sensor 2 Value: ");
  Serial.println(Sensor_2);
  Serial.print("Sensor 3 Value: ");
  Serial.println(Sensor_3);
  Serial.println("-------------------------------------------");
  Serial.println();
  Serial.print("Motor speeds ");
  Serial.print(Right_Speed);
  Serial.print(" - ");
  Serial.print(Left_Speed);

}

void UpdateLineSensorValues(void) {
  Read_IR_Sensor_1();
  Read_IR_Sensor_2();
  Read_IR_Sensor_3();
  //Serial.println(Sensor_2);
}

// ------------------- Identify Color ----------------------- //
int Get_Color(int Sensor_value) {
  //return map(Sensor_value, 0, 500, 0, 100);
  if(Sensor_value < 150) {
    return 0; //Black
  }
  else if (Sensor_value < 400) {
    return 1; //Gray
  }
  else {
    return 2; //White
  }
}
int Get_Color1(int Sensor_value) {
  //return map(Sensor_value, 0, 500, 0, 100);
  if(Sensor_value < 100) {
    return 0; //Black
  }
  else if (Sensor_value < 200) {
    return 1; //Gray
  }
  else {
    return 2; //White
  }
}
// ----------------------------------------------------------- //
