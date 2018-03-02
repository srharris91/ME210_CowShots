/* 
 * Global Variables to be used for every header .h file.
 *
*/
// Global Includes
int timer_gray = 10; // in milliseconds
int timer_stepper = 2000; // in milliseconds
int timer_pulse = 10; //in milliseconds
//IntervalTimer little_Timer;
Metro metroTimer = Metro(timer_gray);
Metro pulseTimer = Metro(timer_pulse);

int Sensor_1_Color;
int Sensor_2_Color;
int Sensor_3_Color;
