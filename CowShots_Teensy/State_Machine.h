// variables and flags
bool resp_To_Gray_Happened=false;

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

// Resp function declarations
void Resp_to_Gray();


// Function Definitions
void handleMoveToA(){
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (Sensor_1_Color_Copy == 1){// if gray detected on far right sensor
        Resp_to_Gray();
        resp_To_Gray_Happened=true;
    }
    if (resp_To_Gray_Happened && metroTimer.check()){
        Line_Sampling_Timer.end(); // stop line following
        Motor_Stop(); // stop motor
        state = STATE_STOP_AT_A;
        resp_To_Gray_Happened=false;
    }
}
void handleStopAtA(){
}
void handleMoveToPatentOffice(){
}
void handleStopAtPatentOffice(){
}
void handleMoveToB(){
}
void handleStopAtB(){
}
void handleMoveToTurn(){
  noInterrupts();
  if (Sensor_1_Color == 0) {
    Line_Sampling_Timer.end();
    metroTimer.interval(100);
    metroTimer.reset();
    state = STATE_WAIT_FOR_TURN;
  }
  interrupts();
}
void handleWaitForTurn() {
  if (metroTimer.check() == 1) {
    TurnRight();
    state = STATE_TAKE_A_TURN;
  }
}
void handleTakeATurn(){
  noInterrupts();
  if (Sensor_3_Color == 0) {
    Setup_Line_Following();
    state = STATE_MOVE_TO_GATE;
  }
  interrupts();
}
void handleMoveToGate(){
}
void handleStopAtGate(){
}


// Resp Function Definitions
void Resp_to_Gray(){// end LineFollow
    metroTimer.interval(timer_gray);
    metroTimer.reset();    
}



