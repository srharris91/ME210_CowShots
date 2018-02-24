#include <IntervalTimer.h>

//Sensor pins
int IR_SENSOR_READ_1 = 14;
int IR_SENSOR_READ_2 = 15;
int IR_SENSOR_READ_3 = 16;

// Sensor values, between 0 and 1024
unsigned int Sensor_1;
unsigned int Sensor_2;
unsigned int Sensor_3;

//Sensor Timer
IntervalTimer Line_Sampling_Timer;

void UpdateLineSensorValues(void);
void PrintLineSensorValues(void);


// --------------------- SETUP FUNCTIONS ------------------------ //
void Setup_Line_Sensors(void) {
  pinMode(IR_SENSOR_READ_1, INPUT);
  pinMode(IR_SENSOR_READ_2, INPUT);
  pinMode(IR_SENSOR_READ_3, INPUT);
}

void Setup_Line_Sampling_Print(void) {
  //Line_Sampling_Timer.begin(PrintLineSensorValues, 500000);
}

void Setup_Line_Sampling(void) {
   //Line_Sampling_Timer.begin(UpdateLineSensorValues, 500000);
}
// --------------------------------------------------------------- //


// ------------------ Read sensor values ------------------------- //
void Read_IR_Sensor_1(void) {
  Sensor_1 = analogRead(IR_SENSOR_READ_1);
}
void Read_IR_Sensor_2(void) {
  Sensor_2 = analogRead(IR_SENSOR_READ_2);
}
void Read_IR_Sensor_3(void) {
  Sensor_3 = analogRead(IR_SENSOR_READ_3);
}
// --------------------------------------------------------------- //


void PrintLineSensorValues(void) {
  Read_IR_Sensor_1();
  Read_IR_Sensor_2();
  Read_IR_Sensor_3();
  Serial.println( "------------ LINE SENSING ----------------");
  Serial.println("Sensor 1 Value:");
  Serial.println(Sensor_1);
  Serial.println("Sensor 2 Value:");
  Serial.println(Sensor_2);
  Serial.println("Sensor 3 Value:");
  Serial.println(Sensor_3);
  Serial.println("-------------------------------------------");
  Serial.println();
}

void UpdateLineSensorValues(void) {
  Read_IR_Sensor_1();
  Read_IR_Sensor_2();
  Read_IR_Sensor_3();
}

