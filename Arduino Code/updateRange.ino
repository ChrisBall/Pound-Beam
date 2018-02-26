void rangeUpdate() {
  if (MB1003.available() > 0) {
    String input = MB1003.readStringUntil('\r'); //read until carriage return
    input.replace("R", "");
    range = input.toInt();
    outputScaleNote = map(range, minRange, maxRange, 0, scaleRange);

    if ((outputScaleNote >= 0) && (outputScaleNote < scaleRange)) {
      notePlaying = true;
    } else {
      notePlaying = false;
    }

    digitalWrite(PWM_RANGE, LOW);
    delay(1);
    digitalWrite(PWM_RANGE, HIGH);
  }
}

//interrupt function: counts PWM width in microseconds and saves value in "range"
//void rangePWM() {
//  long unsigned int us = micros();
//  range = (us - startTime)>5000 ? range : us - startTime; //to get rid of erroneous high values
//  startTime = us;
//}
