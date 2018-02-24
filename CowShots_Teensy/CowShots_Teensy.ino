/*---------------Includes-----------------------------------*/
// #include <Metro.h>
#include <IntervalTimer.h>
// none for now
#include "Motor.h"
#include "Line_Following.h"

/*---------------Module Defines-----------------------------*/
// #define LIGHT_THRESHOLD 172  // trial and error thresholds
// #define LINE_THRESHOLD 10    // trial and error thresholds
// none for now



/*---------------Module Function Prototypes-----------------*/
void blink_LED();
void read_IR();
void Resp_to_key_motor(char);

/*---------------State Definitions--------------------------*/
/* example from Raptor Starter
typedef enum {
  STATE_MOVE_FORWARD, STATE_MOVE_BACKWARD
} States_t;
*/

/*---------------Module Variables---------------------------*/
// motor pins
//int E1 = 20;
//int D1 = 21;
//int E2 = 22;
//int D2 = 23;
//int D1_state = LOW;
//int E1_state = LOW;

// ir beacon pins
int READ_IR1=19;
int inState=0;

// onboard LED
int ledState=LOW;
int ledPin=13;

// timers
IntervalTimer myTimer_LED, myTimer_read;

/*---------------CowShots Main Functions----------------*/
void setup() {
  // put your setup code here, to run once:
  pinMode(READ_IR1, INPUT);
  pinMode(ledPin,OUTPUT);
  Setup_Motor_Pins();
  digitalWrite(ledPin,ledState);
  digitalWrite(E1,E1_state);
  digitalWrite(D1,D1_state);
  Serial.begin(9600);
  myTimer_LED.begin(blink_LED,1000000);
  //myTimer_read.begin(read_IR,1000000);

  Setup_Line_Sampling();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    char key_serial_monitor = Serial.read();
    Serial.print("Read in key: ");
    Serial.println(key_serial_monitor);
    Resp_to_key_motor(key_serial_monitor);
  }
  /*  // example from Raptor Starter
  switch (state) {
    case STATE_MOVE_FORWARD:
      handleMoveForward();
      break;
    case STATE_MOVE_BACKWARD:
      handleMoveBackward();
      break;
    default:    // Should never get into an unhandled state
      Serial.println("What is this I do not even...");
  }
  */
}

/*----------------Module Functions--------------------------*/
void blink_LED(){
  if (ledState==LOW) ledState=HIGH;
  else ledState=LOW;
  digitalWrite(ledPin,ledState);
  //Serial.println("blink_LED called");
}
void read_IR(){
  inState = analogRead(READ_IR1);
  Serial.println(inState);
}
void Resp_to_key_motor(char a){
  if (a=='0'){
    //E1_state=LOW;
    //D1_state=LOW;
    Motor_Stop();
  }
  else if (a=='1'){//direction 1
    GoBackwards();
    
  }
  else if (a=='2'){//direction 2
    GoForward();
  }
  else{
    Serial.println("Key not recognized");
  }
  analogWrite(E1,E1_state);
  digitalWrite(D1,D1_state);
  analogWrite(E2,E2_state);
  digitalWrite(D2,D2_state);
  Serial.print("digitalWrite ");
  Serial.print(E1_state);
  Serial.print(" ");
  Serial.println(D1_state);
}

