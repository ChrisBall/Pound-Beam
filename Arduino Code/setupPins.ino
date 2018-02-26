void setupPins(){
  for(int i=0;i<NUM_BUTTONS;i++){
    pinMode(buttonPins[i],INPUT_PULLUP);
  }
  pinMode(PWM_RANGE,OUTPUT);
  digitalWrite(PWM_RANGE,HIGH);
}

