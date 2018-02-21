/*---------------Includes-----------------------------------*/
// #include <Metro.h>
// none for now

/*---------------Module Defines-----------------------------*/
// #define LIGHT_THRESHOLD 172  // trial and error thresholds
// #define LINE_THRESHOLD 10    // trial and error thresholds
// none for now



/*---------------Module Function Prototypes-----------------*/
void blink_LED();
void read_IR();

/*---------------State Definitions--------------------------*/
/* example from Raptor Starter
typedef enum {
  STATE_MOVE_FORWARD, STATE_MOVE_BACKWARD
} States_t;
*/

/*---------------Module Variables---------------------------*/
int inPin=20;
int inState=0;
int ledState=LOW;
int ledPin=13;
IntervalTimer myTimer_LED, myTimer_read;

/*---------------CowShots Main Functions----------------*/
void setup() {
  // put your setup code here, to run once:
  pinMode(inPin, INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,ledState);
  Serial.begin(9600);
  myTimer_LED.begin(blink_LED,1000000);
  myTimer_read.begin(read_IR,1000000);
}

void loop() {
  // put your main code here, to run repeatedly:
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
  inState = analogRead(inPin);
  Serial.println(inState);
}
