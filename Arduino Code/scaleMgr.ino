void setupSM() {
  sm.init();  //loads three default scales (Chromatic, Major, Minor) into scalemanager
  sm.setScale(MAJOR); //sets the currently used scale to Major
  sm.setFundamental(60); //sets the fundamental to C5 (this is already the default, but included for clarity)
}

