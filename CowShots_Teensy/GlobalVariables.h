/* 
 * Global Variables to be used for every header .h file.
 *
*/
// Global Includes
int timer_gray = 300; // in milliseconds
int timer_push = 300; // in milliseconds
int timer_refill = 1500; // in milliseconds
int timer_moveToRefill = 6000;
//int timer_stepper = 2000; // in milliseconds
int timer_WaitForTurn=200;
int timer_PostTurn = 200;
int timer_PastBlackGate = 1000;
double save_previous_error=0;

//What strategy should we use?
//Protocol 0: Checkoff protocol, no gate detection
//Protocol 1: We cycle going to A, PatentOffice, B, Refill, A...
int Protocol = 0;

//IntervalTimer little_Timer;
Metro metroTimer = Metro(timer_gray);
Metro pushTimer = Metro(timer_push);
Metro metroPostTurn = Metro(timer_PostTurn);
Metro refillTimer = Metro(timer_refill);
Metro moveToRefillTimer = Metro(timer_moveToRefill);
Metro finish210Timer = Metro(130000);
//Metro pulseTimer = Metro(timer_pulse);

int Sensor_1_Color;
int Sensor_2_Color;
int Sensor_3_Color;

