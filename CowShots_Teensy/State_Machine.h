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

void Start_Right_Turn();


// Function Definitions
void handleMoveToA(){
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
  if (Color_1 == 0) {
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
  if (Color_3 == 0) {
    Setup_Line_Following();
    state = STATE_MOVE_TO_GATE;
  }
  interrupts();
}
void handleMoveToGate(){
}
void handleStopAtGate(){
}






