// ---------------------- PINS ------------------------- //
int E1 = 20;
int D1 = 21;
int D1_state = LOW;
int E1_state = LOW;
int E2 = 22;
int D2 = 23;
int D2_state = LOW;
int E2_state = LOW;
// ----------------------------------------------------- //

int DutyCycle = 140;

// ------------------- SETUP MOTOR --------------------- //
void Setup_Motor_Pins(void) {
  pinMode(E1,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(E2,OUTPUT);
  pinMode(D2,OUTPUT);
}
// ----------------------------------------------------- //

void GoBackwards(void) {
    E1_state=DutyCycle;
    D1_state=LOW;
    E2_state=DutyCycle;
    D2_state=LOW;
    //digitalWrite(E1,E1_state);
    //digitalWrite(D1,D1_state);
    //digitalWrite(E2,E2_state);
    //digitalWrite(D2,D2_state);
}

void GoForward(void) {
    E1_state=DutyCycle;
    D1_state=HIGH;
    E2_state=DutyCycle;
    D2_state=HIGH;
    //digitalWrite(E1,E1_state);
    //digitalWrite(D1,D1_state);
    //digitalWrite(E2,E2_state);
    //digitalWrite(D2,D2_state);
}

void Motor_Stop(void) {
    E1_state=0;
    D1_state=LOW;
    E2_state=0;
    D2_state=LOW;
    //digitalWrite(E1,E1_state);
    //digitalWrite(D1,D1_state);
    //digitalWrite(E2,E2_state);
    //digitalWrite(D2,D2_state);
}


