int E1 = 20;
int D1 = 21;
int D1_state = LOW;
int E1_state = LOW;
int E2 = 22;
int D2 = 23;
int D2_state = LOW;
int E2_state = LOW;

void GoBackwards(void) {
    E1_state=HIGH;
    D1_state=LOW;
    E2_state=HIGH;
    D2_state=LOW;
    //digitalWrite(E1,E1_state);
    //digitalWrite(D1,D1_state);
    //digitalWrite(E2,E2_state);
    //#digitalWrite(D2,D2_state);
}

void GoForward(void) {
    E1_state=HIGH;
    D1_state=HIGH;
    E2_state=HIGH;
    D2_state=HIGH;
    //digitalWrite(E1,E1_state);
    //digitalWrite(D1,D1_state);
    //digitalWrite(E2,E2_state);
    //digitalWrite(D2,D2_state);
}

void Motor_Stop(void) {
    E1_state=LOW;
    D1_state=LOW;
    E2_state=LOW;
    D2_state=LOW;
    //digitalWrite(E1,E1_state);
    //digitalWrite(D1,D1_state);
    //digitalWrite(E2,E2_state);
    //digitalWrite(D2,D2_state);
}


