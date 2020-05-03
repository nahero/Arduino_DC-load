//----------------------- Load On/Off --------------------------------
void LoadOn(void) {
  Load = 1;
  analogWrite(StatusLED, 255);
  RelaySwitch("ON");
  if(Mode == "Read") {
    lcd.setCursor(7, 1);
    lcd.print("ON ");
  }
}
void LoadOff(void) {
  Load = 0;
  digitalWrite(StatusLED, LOW);
  RelaySwitch("OFF");
  if(Mode == "Read") {
    lcd.setCursor(7, 1);
    lcd.print("OFF");
  }
}

//----------------------- Set Current --------------------------------
void SetCurrent(void) {
  SetCurrentValue = (CurrentVal1 * 100 + CurrentVal2 * 10 + CurrentVal3) / 100;
  controlVoltage = SetCurrentValue / 5 * 255;
  //  lcd.setCursor(10,0);
  //  lcd.print(SetCurrentValue);
  lcd.setCursor(0, 1);
  lcd.print("     ");
  //  lcd.noCursor();
  lcd.noBlink();
  Mode = "Read";
}

//----------------------- Set Control Voltage ------------------------
float SetControlVoltage(float adjustment) {
  controlVoltage = adjustment / 5 * 255;
}

//----------------------- Set Limits ---------------------------------
void SetLimits(void) {

  Mode = "Settings";

  cycle = 0;
  Serial.print("cycle on setLimits: "); Serial.println(cycle);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set limits:");
  lcd.setCursor(0, 1);    lcd.print(currentLimit, 1);      lcd.print("A");
  lcd.setCursor(5, 1);    
  if(voltageLimit >= 10) { 
    lcd.print(voltageLimit, 0); } else { lcd.print(" "); lcd.print(voltageLimit, 0);    
  } lcd.print("V");
  lcd.setCursor(9, 1);
  if(powerLimit >= 10) { 
    lcd.print(powerLimit, 0); } else { lcd.print(" "); lcd.print(powerLimit, 0);    
  } lcd.print("W");
  lcd.setCursor(13, 1);   lcd.print(temperatureLimit, 0);  lcd.print((char)223);

  lcd.setCursor(2, 1);
  lcd.cursor();

}

//----------------------- Decrease Value --------------------------------
float DecreaseValue(float& value, float valStep, float valMin, float valMax, int pos[]) {

  value -= valStep;
  value = constrain(value, valMin, valMax);

  if(pos[2] == 2 && ((String(value).length()-3) == 1)) {
    lcd.setCursor(pos[0], pos[1]);
    lcd.print(" ");
    lcd.print(value, pos[3]);
    lcd.setCursor(pos[0]+pos[2]-1, pos[1]);
  } else {
    lcd.setCursor(pos[0], pos[1]);
    lcd.print(value, pos[3]);
    lcd.setCursor(pos[0]+pos[2]-1, pos[1]);
  }
  lcd.cursor();

}

//----------------------- Increase Value --------------------------------
float IncreaseValue(float& value, float valStep, float valMin, float valMax, int pos[]) {

  value += valStep;
  value = constrain(value, valMin, valMax);

  if(pos[2] == 2 && ((String(value).length()-3) == 1)) {
    lcd.setCursor(pos[0], pos[1]);
    lcd.print(" ");
    lcd.print(value, pos[3]);
    lcd.setCursor(pos[0]+pos[2]-1, pos[1]);
  } else {
    lcd.setCursor(pos[0], pos[1]);
    lcd.print(value, pos[3]);
    lcd.setCursor(pos[0]+pos[2]-1, pos[1]);
  }
  lcd.cursor();

}

//----------------------- Save Settings ------------------------------
void SaveSettings(void) {

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("SAVED");
  lcd.noCursor();

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(">"); delay(30);
  }
  delay(200);
  lcd.clear();

  Mode = "Read";

  if(TransientsStatus == true) {
    lcd.setCursor(7,0); lcd.print("TR");
  }

}

//----------------------- Set Transients -----------------------
void SetTransients(void) {
  controlVMin   = (int) round(transientMin / 5 * 255);
  controlVMax   = (int) round(transientMax / 5 * 255);
  controlMillis = (int) 1000 / transientFrequency;
}

//----------------------- Limit Warning ------------------------
void LimitWarning(void) {
  lcd.clear();
  lcd.setCursor(0,0);
  if ( current > currentLimit ) {
    lcd.print("CURRENT LIMIT!");
    lcd.setCursor(0,1); lcd.print("> "); lcd.print(currentLimit); lcd.print("A");
  }
  if ( voltage > voltageLimit ) {
    lcd.print("VOLTAGE LIMIT!");
    lcd.setCursor(0,1); lcd.print("> "); lcd.print(voltageLimit); lcd.print("V");
  }
  if ( power > powerLimit ) {
    lcd.print("POWER LIMIT!");
    lcd.setCursor(0,1); lcd.print("> "); lcd.print(powerLimit); lcd.print("W");
  }
  if ( temperature > temperatureLimit ) {
    lcd.print("TEMP LIMIT!");
    lcd.setCursor(0,1); lcd.print("> "); lcd.print(temperatureLimit); 
    lcd.print((char)223); lcd.print("C");
  }
  
  lcd.setCursor(15,1); lcd.cursor(); lcd.blink();
  delay(1500); lcd.noCursor(); lcd.noBlink(); lcd.clear();
}

//----------------------- Toggle Transients Mode -------------
void ToggleTransientsMode(void) {

  if (TransientsStatus == false) {
    LoadOff();
    digitalWrite(FGenPin, HIGH);
    TransientsStatus = true;
    lcd.setCursor(7,0); lcd.print("TR");
  } else {
    LoadOff();
    digitalWrite(FGenPin, LOW);
    TransientsStatus = false;
    lcd.setCursor(7,0); lcd.print("  ");
  }
  
}

//----------------------- Edit Transients --------------------
void EditTransients(void) {

  Mode = "EditTransients";
  cycle = 0;

  lcd.clear();
  
  lcd.setCursor(transientFrequencyPos[0], transientFrequencyPos[1]);    
  lcd.print(transientFrequency, 0);   lcd.print("Hz");

  lcd.setCursor(transientMinPos[0]-3, transientMinPos[1]);   
  lcd.print("Lo");
  
  lcd.setCursor(transientMinPos[0], transientMinPos[1]);   
  lcd.print(transientMin, 2);         lcd.print("A");

  lcd.setCursor(transientMaxPos[0]-3, transientMaxPos[1]);   
  lcd.print("Hi");
  
  lcd.setCursor(transientMaxPos[0], transientMaxPos[1]);   
  lcd.print(transientMax, 2);         lcd.print("A");

  lcd.setCursor(transientFrequencyPos[0], transientFrequencyPos[1]);
  lcd.cursor();

}

//----------------------- Run Transients --------------------
void RunTransients(void) {

  if (currentMillis - previousMillis >= controlMillis) {
      previousMillis = currentMillis;

      controlVoltage = (controlStatus == 0) ? controlVMax : controlVMin;
      analogWrite(ControlPin, controlVoltage);
      controlStatus = !controlStatus;

      Serial.print("controlVoltage: "); Serial.print(controlVoltage);
      Serial.print("\t controlStatus: "); Serial.println(controlStatus);
      Serial.println("--------------------------------------------------");
      
  }
}


//----------------------- Function Generator Mode --------------------
void FunctionGenerator(void) {

  if (FGenStatus == true) {
    digitalWrite(FGenPin, LOW);
    LoadOff();
    FGenStatus = false;
    lcd.setCursor(7,0); lcd.print("  ");
  } else {
    digitalWrite(FGenPin, HIGH);
    LoadOff();
    FGenStatus = true;
    lcd.setCursor(7,0); lcd.print("FG");
  }
  
}

//----------------------- Edit Current -------------------------------
void EditCurrent() {

  Mode = "Edit";

  //  if (digitalRead(CursorToggle) == LOW) {
  //    CP = CP + 1;
  //    delay(200);
  //  }
  if (CP > 3) {
    CP = 0;
  }
  if (CP == 0) {
    lcd.setCursor(10, 0);
    lcd.print(CurrentVal1, 0);
    lcd.setCursor(10, 0);
    //    lcd.cursor();
  }
  else if (CP == 1 || CP == 2) {
    CP = 2;
    lcd.setCursor(12, 0);
    lcd.print(CurrentVal2, 0);
    lcd.setCursor(12, 0);
    //    lcd.cursor();
  }
  else if (CP == 3) {
    lcd.setCursor(13, 0);
    lcd.print(CurrentVal3, 0);
    lcd.setCursor(13, 0);
    //    lcd.cursor();
  }
  //  SetValueUp();
  //  SetValueDown();

}

//----------------------- Print Set Current -------------------------
void PrintSetCurrent(void) {
  lcd.setCursor(0, 1);
  lcd.print("Edit  ");
  lcd.blink();
  SetCurrentValue = (CurrentVal1 * 100 + CurrentVal2 * 10 + CurrentVal3) / 100;
  lcd.setCursor(10, 0);
  lcd.print(SetCurrentValue);
}

//----------------------- Set Value Up -------------------------
float LimitUp(float valueToChange, int valueStep) {

  valueToChange += valueStep;
  return valueToChange;
}

//----------------------- Set Value Down -------------------------
float LimitDown(float valueToChange, int valueStep) {

  valueToChange -= valueStep;
  return valueToChange;
}


//----------------------- Set Value Up -------------------------
void SetValueUp(void) {

  if (CP == 0) {
    CurrentVal1 = constrain(CurrentVal1, 0, 5);
    CurrentVal1 += 1;
    lcd.setCursor(10, 0);
  } else if (CP == 2) {
    CurrentVal2 = constrain(CurrentVal2, 0, 9);
    CurrentVal2 += 1;
    lcd.setCursor(12, 0);
  } else if (CP == 3) {
    CurrentVal3 = constrain(CurrentVal3, 0, 9);
    CurrentVal3 += 1;
    lcd.setCursor(13, 0);
  }
}

//----------------------- Set Value Down -------------------------
void SetValueDown(void) {

  if (CP == 0) {
    CurrentVal1 -= 1;
    CurrentVal1 = constrain(CurrentVal1, 0, 6);
    lcd.setCursor(10, 0);
  } else if (CP == 2) {
    CurrentVal2 -= 1;
    CurrentVal2 = constrain(CurrentVal2, 0, 9.1);
    lcd.setCursor(12, 0);
  } else if (CP == 3) {
    CurrentVal3 -= 1;
    CurrentVal3 = constrain(CurrentVal3, 0, 9.1);
    lcd.setCursor(10, 0);
  }
}

//----------------------- Dynamically Adjust Current -----------------
//void ControlAdjust(void) {
//
//  Serial.print("current = ");
//  Serial.print(current);
//  Serial.print("\t SetCurrentValue = ");
//  Serial.println(SetCurrentValue);
//
//  if ( abs(current - SetCurrentValue) > 0.05) {
//
//    if (currentMillis - previousMillis >= 1000) {
//      previousMillis = currentMillis;
//
//      float diff = abs(current - SetCurrentValue);
//      diff = constrain(diff, 0, 0.3);
//
//      Serial.print("diff = ");
//      Serial.println(diff);
//
//      if (current < SetCurrentValue) {
//        adjustment = SetCurrentValue + (diff / 2);
//      } else {
//        adjustment = SetCurrentValue - (diff / 2);
//      }
//      float adjMax = SetCurrentValue * 1.2;
//      adjustment = constrain(adjustment, 0, adjMax);
//
//
//      Serial.print("adjustment = ");
//      Serial.println(adjustment);
//
//      SetControlVoltage(adjustment);
//
//    }
//
//  }
//
//}


//-------------------------- Potentiometer Set Value -----------------
//void PotSetValue() {
//
//    int currentPotValue = analogRead(PotInputPin);
//
//    if( abs(currentPotValue - potValue) > 30) {
//      potValue = currentPotValue;
//
//      if(CP == 0) {
//        PotReadA = map(potValue, 0, 980, 0, 5);
////        lcd.setCursor(10,0);
////        lcd.print(PotReadA,0);
//      } else if (CP == 2) {
//        PotReadB = map(potValue, 0, 980, 0, 9);
////        lcd.setCursor(12,0);
////        lcd.print(PotReadB,0);
//      } else if (CP == 3) {
//        PotReadC = map(potValue, 0, 980, 0, 9);
////        lcd.setCursor(13,0);
////        lcd.print(PotReadC,0);
//      }
//      delay(20);
//    }
//}

/* Test control voltage ************************/
//void testPWMvoltage(void) {
//
//  for (int counter = 0; counter < 20; counter++) {
//    controlVoltage = map(counter, 0, 1023, 0, 255);
//    analogWrite(ControlPin, controlVoltage);
//
//    float controlVoltage = analogRead(voltageCheck) * 5.00 / 1023;
//
//    Serial.print("counter = ");
//    Serial.print(counter);
//    Serial.print("\t controlPWM = ");
//    Serial.print(controlVoltage);
//    Serial.print("\t voltage = ");
//    Serial.println(controlVoltage);
//
//    delay(2000);
//    }
//}
