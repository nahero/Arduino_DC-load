void loop() {

  LoadOnOff.read();
  if (LoadOnOff.changed()) {
    Load == 0 ? LoadOn() : LoadOff();
  }

  SetButton.read();
  if (SetButton.changed()) {
    if (Mode == "Settings") { SaveSettings(); }
    else if (Mode == "EditTransients") { SaveSettings(); }
    else { SetLimits(); }
  }

  if ( Load == 1 && TransientsStatus == true ) {
    SetTransients();
    RunTransients();
  }
    

  // LIMITS
  if ( temperature > temperatureLimit ||
       power > powerLimit ||
       current > currentLimit ||
       voltage > voltageLimit ) {
    LoadOff();
    LimitWarning();
  }

  // Prevent Reading in Edit mode because of cursor behaviour
  if ( Mode == "Read" || Mode == "TransientsMode" ) {
    ReadCurrent();
    ReadVoltage();
    CalculatePower();
    ReadTemperature();
  }

  CursorToggle.read();
  if (Mode == "Settings") {
    if ( CursorToggle.wasReleased() ) { 
      CursorCycle(3,currentLimitPos,voltageLimitPos,powerLimitPos,tempLimitPos); 
      }
  } else if (Mode == "Read" && TransientsStatus == true) {
    CursorToggle.wasReleased() ? EditTransients() : void();
  } else if (Mode == "EditTransients") {
    if ( CursorToggle.wasReleased() ) {
      CursorCycle(2,transientFrequencyPos,transientMinPos,transientMaxPos,transientMaxPos);
    }
  }
  
  ValueDown.read();
  if (ValueDown.wasReleased()) {
    if (Mode == "Settings") {
      if (cycle == 0) {
        DecreaseValue(currentLimitRef, 0.1, 0.1, 5, currentLimitPos);
      } else if (cycle == 1) {
        DecreaseValue(voltageLimitRef, 1, 1, 50, voltageLimitPos);
      } else if (cycle == 2) {
        DecreaseValue(powerLimitRef, 1, 1, 99, powerLimitPos);
      } else if (cycle == 3) {
        DecreaseValue(tempLimitRef, 1, 30, 60, tempLimitPos);
      }
    } else if (Mode == "EditTransients") {
      if (cycle == 0) {
        DecreaseValue(transientFrequencyRef, 10, 1, 10000, transientFrequencyPos);
      } else if (cycle == 1) {
        DecreaseValue(transientMinRef, 0.1, 0, 4, transientMinPos);
      } else if (cycle == 2) {
        DecreaseValue(transientMaxRef, 0.1, 0.1, 4, transientMaxPos);
      } 
    }
  }
  
  ValueUp.read();
  if (ValueUp.wasReleased()) {
    if (Mode == "Settings") {
      if (cycle == 0) {
        IncreaseValue(currentLimitRef, 0.1, 0.1, 5, currentLimitPos);
      } else if (cycle == 1) {
        IncreaseValue(voltageLimitRef, 1, 1, 50, voltageLimitPos);
      } else if (cycle == 2) {
        IncreaseValue(powerLimitRef, 1, 1, 99, powerLimitPos);
      } else if (cycle == 3) {
        IncreaseValue(tempLimitRef, 1, 30, 60, tempLimitPos);
      }
    } else if (Mode == "EditTransients") {
      if (cycle == 0) {
        IncreaseValue(transientFrequencyRef, 10, 1, 10000, transientFrequencyPos);
      } else if (cycle == 1) {
        IncreaseValue(transientMinRef, 0.1, 0, 4, transientMinPos);
      } else if (cycle == 2) {
        IncreaseValue(transientMaxRef, 0.1, 0.1, 4, transientMaxPos);
      } 
    } else if (Mode == "Read") {
      ToggleTransientsMode();
    }
  }

  currentMillisA = millis();
  currentMillisV = millis();
  currentMillisP = millis();
  currentMillisT = millis();
  currentMillis  = millis();
  

}
