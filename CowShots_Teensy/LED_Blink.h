// onboard LED
int ledState=LOW;
int ledPin=13;

IntervalTimer myTimer_LED;


void blink_LED(){
  if (ledState==LOW) ledState=HIGH;
  else ledState=LOW;
  digitalWrite(ledPin,ledState);
  //Serial.println("blink_LED called");
}
void Setup_LED_Blink(){
  myTimer_LED.begin(blink_LED,1000000);
}

