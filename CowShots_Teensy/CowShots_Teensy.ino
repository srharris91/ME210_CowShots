/*---------------Includes-----------------------------------*/
#include <IntervalTimer.h>
#include <AccelStepper.h>
#include <Metro.h>
#include "GlobalVariables.h"
// CowShots created header files
#include "LED_Blink.h"

#include "Motor.h"          // functions to control the motor
#include "Stepper.h"

// global variables needed for both Line sensing and Line following
#include "Line_Sensing.h"   // function to sense the line
#include "Line_Following.h" // function to follow the line
#include "State_Machine.h"

/*---------------Module Defines-----------------------------*/
// #define LIGHT_THRESHOLD 172  // trial and error thresholds
// #define LINE_THRESHOLD 10    // trial and error thresholds



/*---------------Module Function Prototypes-----------------*/
void blink_LED();
void Resp_to_key_motor(char);

/*---------------State Definitions--------------------------*/

/*---------------Module Variables---------------------------*/



/*---------------CowShots Main Functions----------------*/
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,ledState);
  Serial.begin(9600);

  Setup_LED_Blink();
  Setup_Motor_Pins();
  Setup_Line_Sensors();

  //Initialize actions for the first state
  //Setup_Line_Following();
  Setup_Line_Following_PID();
  //GoForward();
  //state=STATE_TEST;
  state = STATE_MOVE_TO_A;
  //state = STATE_STOP_AT_B;
  //state = STATE_MOVE_TO_TURN;

  //Setup_Line_Sampling_Print();
  Setup_Stepper();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    char key_serial_monitor = Serial.read();
    Serial.print("Read in key: ");
    Serial.println(key_serial_monitor);
    Resp_to_key_motor(key_serial_monitor);
  }
  //Follow_Line();
  //stepmotor.setSpeed(140);
  //stepmotor.runSpeed();
  switch (state) {
    case STATE_MOVE_TO_A:
      handleMoveToA();
      break;
    case STATE_STOP_AT_A:
      handleStopAtA();
      break;
    case STATE_MOVE_TO_PATENT_OFFICE:
      handleMoveToPatentOffice();
      break;
    case STATE_STOP_AT_PATENT_OFFICE:
      handleStopAtPatentOffice();
      break;
    case STATE_MOVE_TO_B:
      handleMoveToB();
      break;
    case STATE_STOP_AT_B:
      handleStopAtB();
      break;
    case STATE_MOVE_TO_TURN:
      handleMoveToTurn();
      break;
    case STATE_WAIT_FOR_TURN:
      handleWaitForTurn();
      break;
    case STATE_TAKE_A_TURN:
      handleTakeATurn();
      break;
    case STATE_MOVE_TO_GATE:
      handleMoveToGate();
      break;
    case STATE_STOP_AT_GATE:
      handleStopAtGate();
      break;
    case STATE_TEST:
      break;
    default:    // Should never get into an unhandled state
      Serial.print("What is this I do not even...");
      Serial.println(state);
  }
  stepmotor.run();
}

/*----------------Module Functions--------------------------*/
void Resp_to_key_motor(char a){
  if (a=='0'){
    //E1_state=LOW;
    //D1_state=LOW;
    
    state=STATE_TEST;
    Line_Sampling_Timer.end();
    Motor_Stop();
  }
  else if (a=='1'){//direction 1
    state=STATE_TEST;
    GoBackwards();
    
  }
  else if (a=='2'){//direction 2
    GoForward();
    state=STATE_TEST;

  }
  else if (a=='s'){// stepper motor go
    //runsteppermotor();
    //stepmotor.setSpeed(1400);
    stepmotor.move(10);
    Serial.println("Stepper Motor moved one");
  }
  else if (a=='c'){// check if stepper motor is done
    Serial.print("DistanceToGo = ");
    Serial.println(stepmotor.distanceToGo());
  }
  else if (a=='l'){// what is my line sensor 1 reading?
    UpdateLineSensorValues();
    Sensor_1_Color = Get_Color1(Sensor_1);
    Sensor_2_Color = Get_Color(Sensor_2);
    Sensor_3_Color = Get_Color(Sensor_3);

    Serial.println("Your line sensor 1 is reading ");
    Serial.print(Sensor_1_Color);
    Serial.print(" ");
    Serial.println(Sensor_1);
    Serial.print(Sensor_2_Color);
    Serial.print(" ");
    Serial.println(Sensor_2);
    Serial.print(Sensor_3_Color);
    Serial.print(" ");
    Serial.println(Sensor_3);
  }
  else if (a=='t'){// what state am I in?
    Serial.print("You are in state = ");
    Serial.println(state);
  }
  else if (a=='r'){
    noInterrupts();
    Serial.print("Correction = ");
    Serial.println(correction);
    Serial.print("error = ");
    Serial.println(error);
    interrupts();
  }
  else{
    Serial.println("Key not recognized");
  }
  analogWrite(E1,E1_state);
  digitalWrite(D1,D1_state);
  analogWrite(E2,E2_state);
  digitalWrite(D2,D2_state);
  //Serial.print("digitalWrite ");
  //Serial.print(E1_state);
  //Serial.print(" ");
  //Serial.println(D1_state);
}

