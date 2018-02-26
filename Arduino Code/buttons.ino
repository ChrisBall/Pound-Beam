//this function manages 4-state buttons (pressed, held, released, off)
void buttonUpdate() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    boolean buttonState = digitalRead(buttonPins[i]);
    if (buttonStates[i] == 3) {
      buttonStates[i] = 2;
    }
    if ((buttonState == LOW) && (buttonStates[i] == 0)) {
      buttonStates[i] = 3;
    }
    if (buttonStates[i] == 1) {
      buttonStates[i] = 0;
    }
    if ((buttonState == HIGH) && (buttonStates[i] == 2)) {
      buttonStates[i] = 1;
    }
  }
  //0-off
  //3-momentary on
  //2-on
  //1-momentary off
}

//this function acts upon button presses
void buttonActions() {
  if (buttonStates[UP] == 3) {
    activeMenuInput--;
  }

  if (buttonStates[DOWN] == 3) {
    activeMenuInput++;
  }

  if (buttonStates[LEFT] == 3) {
    switch (activeMenuInput) {
      case 0:
        sm.fundamental = constrain(sm.fundamental - 1, 0, 127);
        break;
      case 1:
        scaleRange = constrain(scaleRange - 1, 1, 36);
        break;
      case 2:
        minRange = constrain(minRange - 10, 300, maxRange - 10);
        break;
      case 3:
        maxRange = constrain(maxRange - 10, minRange + 10, 5000);
        break;
      case 4:
        midiInstrument = constrain(midiInstrument - 1, 0, 127);
        midiSetChannelBank(0, VS1053_BANK_MELODY);
        midiSetInstrument(0, midiInstrument);
        break;
    }
  }

  if (buttonStates[CENTRE] == 3) {
    switch (activeMenuInput) {
      case 0:
        sm.currentScale = (sm.currentScale + 1) % 8;
        break;
    }
  }

  if (buttonStates[RIGHT] == 3) {
    switch (activeMenuInput) {
      case 0:
        sm.fundamental = constrain(sm.fundamental + 1, 0, 127);
        break;
      case 1:
        scaleRange = constrain(scaleRange + 1, 1, 36);
        break;
      case 2:
        minRange = constrain(minRange + 10, 300, maxRange - 10);
        break;
      case 3:
        maxRange = constrain(maxRange + 10, minRange + 10, 5000);
        break;
      case 4:
        midiInstrument = constrain(midiInstrument + 1, 0, 127);
        midiSetChannelBank(0, VS1053_BANK_MELODY);
        midiSetInstrument(0, midiInstrument);
        break;
    }
  }

  if (activeMenuInput < 0) {
    activeMenuInput = menuItems - 1; //menu looping
  } else if (activeMenuInput > (menuItems - 1)) {
    activeMenuInput = 0;
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (buttonStates[i] == 1) { //if a button has been pressed
      drawMenu();            //update the menu
      return;
    }
  }
}

