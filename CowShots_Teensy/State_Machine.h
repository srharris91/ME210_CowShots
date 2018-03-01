// State machine
typedef enum {
    STATE_MOVE_TO_A,
    STATE_STOP_AT_A,
    STATE_MOVE_TO_PATENT_OFFICE,
    STATE_STOP_AT_PATENT_OFFICE,
    STATE_MOVE_TO_B,
    STATE_STOP_AT_B,
    STATE_MOVE_TO_TURN,
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
void handleTakeATurn();
void handleMoveToGate();
void handleStopAtGate();


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
}
void handleTakeATurn(){
}
void handleMoveToGate(){
}
void handleStopAtGate(){
}






