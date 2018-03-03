/*
 * Functions to be used to output motor control
*/

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

int DutyCycle = 40; //Our reference speed
int Max_Speed = 200; //We use this to apply saturation
int Right_Speed = DutyCycle;
int Left_Speed = DutyCycle;
int Right_Direction = LOW; //These could eventually replace D1_state if it works out
int Left_Direction = LOW;

// ------------------- SETUP MOTOR --------------------- //
void Setup_Motor_Pins(void) {
  pinMode(E1,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(E2,OUTPUT);
  pinMode(D2,OUTPUT);
}
// ----------------------------------------------------- //


// ----------------- Custom Moving --------------------- //
void Advance(void) {
  //Serial.println(Left_Speed);
  //Serial.println(Right_Speed);
  E1_state = Left_Speed;
  D1_state=Left_Direction;
  E2_state = Right_Speed;
  D2_state=Right_Direction;
  analogWrite(E1,E1_state);
  digitalWrite(D1,D1_state);
  analogWrite(E2,E2_state);
  digitalWrite(D2,D2_state);
}

// ------------------------------------------------------ //

// ----------------- Elementary Moving ------------------ //

void TurnRight(void) {
    E1_state=80;
    D1_state=HIGH;
    E2_state=80;
    D2_state=LOW;
    analogWrite(E1,E1_state);
    digitalWrite(D1,D1_state);
    analogWrite(E2,E2_state);
    digitalWrite(D2,D2_state);
}

void Start_Pulse(void) {
    E1_state=200;
    D1_state=HIGH;
    E2_state=200;
    D2_state=HIGH;
    analogWrite(E1,E1_state);
    digitalWrite(D1,D1_state);
    analogWrite(E2,E2_state);
    digitalWrite(D2,D2_state);
}

void GoBackwards(void) {
    E1_state=DutyCycle;
    D1_state=LOW;
    E2_state=DutyCycle;
    D2_state=LOW;
    analogWrite(E1,E1_state);
    digitalWrite(D1,D1_state);
    analogWrite(E2,E2_state);
    digitalWrite(D2,D2_state);
}

void GoForward(void) {
    E1_state=DutyCycle;
    D1_state=HIGH;
    E2_state=DutyCycle-4;
    D2_state=HIGH;
    analogWrite(E1,E1_state);
    digitalWrite(D1,D1_state);
    analogWrite(E2,E2_state);
    digitalWrite(D2,D2_state);
}

void Motor_Stop(void) {
    E1_state=LOW;
    D1_state=LOW;
    E2_state=LOW;
    D2_state=LOW;
    analogWrite(E1,E1_state);
    digitalWrite(D1,D1_state);
    analogWrite(E2,E2_state);
    digitalWrite(D2,D2_state);
}
// -------------------------------------------------------- //
