//----------------------- Relay On/Off --------------------------------------
void RelaySwitch(String relayToggle) {
  int relayToggleValue = (relayToggle == "ON") ? 255 : 0;
  analogWrite(RelayOnOff, relayToggleValue);
}

//----------------------- Cursor Cycle --------------------------------------
int CursorCycle(int cycleMax, int a[], int b[], int c[], int d[]) {
  
//    Serial.print("cycle: ");
//    Serial.println(cycle);
    cycle += 1;

  if (cycle > cycleMax) {
    cycle = 0;
  }
  if (cycle == 0) {
    lcd.setCursor(a[0]+a[2]-1, a[1]);
    lcd.cursor();    
  }
  else if (cycle == 1) {
    lcd.setCursor(b[0]+b[2]-1, b[1]);
    lcd.cursor();
  }
  else if (cycle == 2) {
    lcd.setCursor(c[0]+c[2]-1, c[1]);
    lcd.cursor();
  }
  else if (cycle == 3) {
    lcd.setCursor(d[0]+d[2]-1, d[1]);
    lcd.cursor();
  }
}

//----------------------- Value Up Button --------------------------------
//void ValueUpButton(void) {
//  int buttonRead = !digitalRead(ValueUp);
//  if (buttonRead != ValueUp_lastState) {
//    lastDebounceTime = millis();
//  }
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    if (buttonRead != ValueUp_state) {
//      ValueUp_state = buttonRead;
//
//      if (ValueUp_state == HIGH) {
//
//        SetValueUp();
//
//      }
//    }
//  }
//  ValueUp_lastState = buttonRead;
//}

//----------------------- Value Down Button --------------------------------
//void ValueDownButton(void) {
//  int buttonRead = !digitalRead(ValueDown);
//  if (buttonRead != ValueDown_lastState) {
//    lastDebounceTime = millis();
//  }
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    if (buttonRead != ValueDown_state) {
//      ValueDown_state = buttonRead;
//
//      if (ValueDown_state == HIGH) {
//
//        SetValueDown();
//
//      }
//    }
//  }
//  ValueDown_lastState = buttonRead;
//}
