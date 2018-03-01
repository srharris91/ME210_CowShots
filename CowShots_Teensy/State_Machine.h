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

// Resp function declarations
void Resp_to_Gray();


// Function Definitions
void handleMoveToA(){
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (Sensor_1_Color_Copy == 1){// if gray detected on far right sensor
        Resp_to_Gray();
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
}
void handleTakeATurn(){
}
void handleMoveToGate(){
}
void handleStopAtGate(){
}


// Resp Function Definitions
void Resp_to_Gray(){// end LineFollow
    metroTimer.interval(timer_gray);
    metroTimer.reset();
    if (metroTimer.check()){
        Line_Sampling_Timer.end(); // stop line following
        Motor_Stop(); // stop motor
        state = STATE_STOP_AT_A;
    }
}



