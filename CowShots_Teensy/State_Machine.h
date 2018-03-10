// variables and flags
bool resp_To_Gray_Happened=false;
bool resp_Move_Stepper_Motor=false;
bool TakeATurnHappened=false;
// State machine
typedef enum {
    STATE_MOVE_TO_A,
    STATE_STOP_AT_A,
    STATE_MOVE_TO_PATENT_OFFICE,
    STATE_STOP_AT_PATENT_OFFICE,
    STATE_MOVE_TO_B,
    STATE_STOP_AT_B,

    
    STATE_MOVE_TO_TURN,
    STATE_WAIT_FOR_TURN,
    STATE_TAKE_A_TURN,
    STATE_MOVE_TO_GATE,
    STATE_STOP_AT_GATE,

    STATE_B_TO_REFILL, // Go back to the black line
    STATE_MOVE_TO_REFILL, // once past the black line, go to the gray refill line
    STATE_PUSH_BUTTON, // Manoever button
    STATE_REFILL, //Wait for us (timer?)

    
    STATE_TEST,
} States_t;

// State variable
States_t state;

// Function declarations
void handleMoveToA();
void handleStopAtA();
void handleMoveToPatentOffice();
void handleStopAtPatentOffice();
void handleMoveToB();
void handleStopAtB();

void handleMoveToTurn();
void handleWaitForTurn();
void handleTakeATurn();
void handleMoveToGate();
void handleStopAtGate();

void handleBToRefill();
void handleMoveToRefill();
void handlePushButton();
void handleRefill();

// Resp function declarations
void Resp_to_Gray();


// Function Definitions

// ------------------------ PLACING BALLS STATES ---------------------------------- //
void handleMoveToA(){
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (Sensor_1_Color_Copy == 1){// if gray detected on far right sensor
        Resp_to_Gray();
        resp_To_Gray_Happened=true;
    }
    if (resp_To_Gray_Happened && metroTimer.check()){
        //Line_Sampling_Timer.end(); // stop line following
        Stop_Line_Following_PID();
        Motor_Stop(); // stop motor
        state = STATE_STOP_AT_A;
        Serial.println("state set to STATE_STOP_AT_A");
        resp_To_Gray_Happened=false;
    }
}
void handleStopAtA(){
    if (resp_Move_Stepper_Motor==false){
        Move_Stepper_Motor();
        resp_Move_Stepper_Motor=true;
    }
    Run_Stepper_Motor();
    if (stepmotor.distanceToGo() == 0){
        Setup_Line_Following_PID();
        state = STATE_MOVE_TO_PATENT_OFFICE;
        Serial.println("state set to STATE_MOVE_TO_PATENT_OFFICE");
        resp_Move_Stepper_Motor=false;
    }
}
void handleMoveToPatentOffice(){
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (Sensor_1_Color_Copy == 1){// if gray detected on far right sensor
        Resp_to_Gray();
        resp_To_Gray_Happened=true;
    }
    if (resp_To_Gray_Happened && metroTimer.check()){
        //Line_Sampling_Timer.end(); // stop line following
        Stop_Line_Following_PID();
        Motor_Stop(); // stop motor
        state = STATE_STOP_AT_PATENT_OFFICE;
        Serial.println("state set to STATE_STOP_AT_PATENT_OFFICE");
        resp_To_Gray_Happened=false;
    }
}
void handleStopAtPatentOffice(){
    if (resp_Move_Stepper_Motor==false){
        Move_Stepper_Motor();
        resp_Move_Stepper_Motor=true;
    }
    Run_Stepper_Motor();
    if (stepmotor.distanceToGo() == 0){
        Setup_Line_Following_PID();
        state = STATE_MOVE_TO_B;
        Serial.println("state set to STATE_MOVE_TO_B");
        resp_Move_Stepper_Motor=false;

    }
}
void handleMoveToB(){
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (Sensor_1_Color_Copy == 1){// if gray detected on far right sensor
        Resp_to_Gray();
        resp_To_Gray_Happened=true;
    }
    if (resp_To_Gray_Happened && metroTimer.check()){
        //Line_Sampling_Timer.end(); // stop line following
        Stop_Line_Following_PID();
        Motor_Stop(); // stop motor
        state = STATE_STOP_AT_B;
        Serial.println("state set to STOP_AT_B");
        resp_To_Gray_Happened=false;
    }
}
void handleStopAtB(){
    if (resp_Move_Stepper_Motor==false){
        Move_Stepper_Motor();
        resp_Move_Stepper_Motor=true;
    }
    Run_Stepper_Motor();

    //CASE WHERE WE GO TO TURN
    if (Protocol == 0) {
      if (stepmotor.distanceToGo() == 0){
          Setup_Line_Following_PID();
          state = STATE_MOVE_TO_TURN;
          Serial.println("state set to MOVE_TO_TURN");
          resp_Move_Stepper_Motor=false;
      }
    }

    //CASE WHERE WE GO TO REFILL
    else if (Protocol == 1) {
      if (stepmotor.distanceToGo() == 0){
          Setup_Line_Following_Backwards_PID();
          state = STATE_B_TO_REFILL;
          Serial.println("state set to B_TO_REFILL");
          resp_Move_Stepper_Motor=false;
      }
    }   
}





// ------------------------- REFILLING STATES -------------------------------- //
void handleBToRefill(){
  noInterrupts();
  int Sensor_1_Color_Copy = Sensor_1_Color;
  interrupts();

  if (Sensor_1_Color_Copy == 0) {
    Resp_to_Gray();
    resp_To_Gray_Happened=true;
  }
  if (resp_To_Gray_Happened && metroTimer.check()){
        state = STATE_MOVE_TO_REFILL;

        moveToRefillTimer.interval(timer_moveToRefill);
        moveToRefillTimer.reset();
        Serial.println("state set to MOVE_TO_REFILL");
        resp_To_Gray_Happened=false;
    }
}

void handleMoveToRefill() {

  if (moveToRefillTimer.check()) {
    Stop_Line_Following_Backwards_PID();
    Motor_Stop(); // stop motor
    state = STATE_PUSH_BUTTON;
    metroTimer.interval(timer_push);
    metroTimer.reset(); 
    Serial.println("state set to PUSH_BUTTON");
    Push_Manoever_1();
  }
}

void handlePushButton() {
  if (metroTimer.check()) {
    Push_Manoever_2();
    pushTimer.interval(timer_push);
    pushTimer.reset(); 
  }
  if (metroTimer.check() && pushTimer.check()) {
    Motor_Stop(); // stop motor
    state = STATE_REFILL;
    refillTimer.interval(timer_refill);
    refillTimer.reset();
  }
}

void handleRefill() {
  if (refillTimer.check()) {
    Setup_Line_Following_PID();
    state = STATE_MOVE_TO_A;
  }
}




// ------------------------------ TURNING STATES ------------------------------- //
void handleMoveToTurn(){
  noInterrupts();
  Sensor_1_Color = Get_Color1(Sensor_1);
  interrupts();

  if (Sensor_1_Color == 0) {
    //Line_Sampling_Timer.end();
    Stop_Line_Following_PID();
    //Setup_Line_Sampling;
    //TurnRight();
    metroTimer.interval(timer_WaitForTurn);
    metroTimer.reset();
    state = STATE_WAIT_FOR_TURN;
    Serial.println("state set to WAIT_FOR_TURN");
  }
}
void handleWaitForTurn() {
  if (metroTimer.check() == 1) {
    
    TurnRight();
    save_previous_error = 0;
    state = STATE_TAKE_A_TURN;
    Serial.println("state set to TAKE_A_TURN");
  }
}
void handleTakeATurn(){
  
  UpdateLineSensorValues();
  noInterrupts();
  Sensor_2_Color = Get_Color(Sensor_2);
  interrupts();

  if (Sensor_2_Color == 0) {
    //Stop_Line_Sampling();
    //DutyCycle=43;
    DutyCycle=25;
    Setup_Line_Following_PID();
    state = STATE_MOVE_TO_GATE;
    Serial.println("state set to MOVE_TO_GATE");
    //Motor_Stop();
    metroTimer.interval(timer_gray);
    metroTimer.reset();
    metroPostTurn.interval(timer_PostTurn);
    metroPostTurn.reset();
  }
  
}
void handleMoveToGate(){
    //UpdateLineSensorValues();
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (DutyCycle<40 && metroPostTurn.check()){
      DutyCycle++;
    }
    if (TakeATurnHappened==false && metroTimer.check()){
       TakeATurnHappened=true;
       Serial.println("TakeATurnHappened");
    }
    if (resp_To_Gray_Happened==false && TakeATurnHappened && Sensor_1_Color_Copy == 0){// if black detected on far right sensor
        metroTimer.interval(timer_PastBlackGate);//Resp_to_Gray();
        metroTimer.reset();
        resp_To_Gray_Happened=true;
        Serial.println("RespToGrayHappened");
    }
    if (TakeATurnHappened && resp_To_Gray_Happened && metroTimer.check()){
        //Line_Sampling_Timer.end(); // stop line following
        Stop_Line_Following_PID();
        Motor_Stop(); // stop motor
        state = STATE_STOP_AT_GATE;
        Serial.println("state set to STOP_AT_GATE");
        resp_To_Gray_Happened=false;
    }
}
void handleStopAtGate(){
}


// Resp Function Definitions
void Resp_to_Gray(){// end LineFollow
    metroTimer.interval(timer_gray);
    metroTimer.reset();    
}



