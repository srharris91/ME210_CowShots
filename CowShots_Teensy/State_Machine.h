// variables and flags
bool resp_To_Gray_Happened=false;
bool resp_Move_Stepper_Motor=false;

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
    if (stepmotor.distanceToGo() == 0){
        Setup_Line_Following_PID();
        state = STATE_MOVE_TO_TURN;
        Serial.println("state set to MOVE_TO_TURN");
        resp_Move_Stepper_Motor=false;
    }
}
void handleMoveToTurn(){
  noInterrupts();
  Sensor_1_Color = Get_Color1(Sensor_1);
  interrupts();

  if (Sensor_1_Color == 0) {
    //Line_Sampling_Timer.end();
    Stop_Line_Following_PID();
    Setup_Line_Sampling;
    TurnRight();
    metroTimer.interval(timer_WaitForTurn);
    metroTimer.reset();
    state = STATE_WAIT_FOR_TURN;
    Serial.println("state set to WAIT_FOR_TURN");
  }
}
void handleWaitForTurn() {
  if (metroTimer.check() == 1) {
    Stop_Line_Sampling();
    TurnRight();
    state = STATE_TAKE_A_TURN;
    Serial.println("state set to TAKE_A_TURN");
  }
}
void handleTakeATurn(){
  UpdateLineSensorValues();
  noInterrupts();
  Sensor_3_Color = Get_Color(Sensor_3);
  interrupts();

  if (Sensor_3_Color == 0) {
    
    Setup_Line_Following_PID();
    state = STATE_MOVE_TO_GATE;
    Serial.println("state set to MOVE_TO_GATE");
    //Motor_Stop();
  }
}
void handleMoveToGate(){
    noInterrupts();
    int Sensor_1_Color_Copy = Sensor_1_Color;
    interrupts();
    if (Sensor_1_Color_Copy == 0){// if black detected on far right sensor
        Resp_to_Gray();
        resp_To_Gray_Happened=true;
    }
    if (resp_To_Gray_Happened && metroTimer.check()){
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



