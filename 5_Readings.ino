//----------------------- Read Current ---------------------------
void ReadCurrent() {

  if ( Mode == "Settings" ) {
    return;
  } else {

    if (currentMillisA - previousMillisA >= 400) {
      previousMillisA = currentMillisA;

      int currentRead = analogRead(CurrentPin);

      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
      current = currentRead * (5.0 / 1023.0) * 4 / 3; // because of divider
      if (current > 0) {    // prevent Current to show 0.07 when actually 0
        current = current + ( 0.07 - 0.049 * current );
      }
      lcd.setCursor(10, 0);
      lcd.print(current, 2);
      lcd.print(" A");

    }
  }
}

//----------------------- Read Voltage ---------------------------
void ReadVoltage() {
  if (currentMillisV - previousMillisV >= 500) {
    previousMillisV = currentMillisV;

    int voltageRead = analogRead(VoltagePin);
    voltage = voltageRead * (5.0 / 1023.0) * 10; // x10 because of divider
//    Serial.print("voltageRead: ");
//    Serial.print(voltageRead);
//    Serial.print("\t voltage: ");
//    Serial.println(voltage);
    //    Serial.print("voltage2 ");
    //    Serial.print(voltage2);


    //    Voltage adjust
    //    float voltAdj = (current - 1) / 0.5 * 0.15;
    float voltAdj = (current - (current / 3)) * 0.2;
    voltage += voltAdj;

    int voltageLength = String(voltage).length() + 1;
    lcd.setCursor(0, 0);
    lcd.print(voltage, 1);
    lcd.print(" V ");
    //  Serial.println(voltage);
    //  delay(10);
  }
}

//----------------------- Calculate Power ---------------------------
void CalculatePower() {
  if (currentMillisP - previousMillisP >= 500) {
    previousMillisP = currentMillisP;
    power = current * voltage;
    int powerLength = String(power).length();

    if (powerLength == 1) {
      lcd.setCursor(11, 1);
      lcd.print("  ");
      lcd.print(power);
    } else if (powerLength == 2) {
      lcd.setCursor(11, 1);
      lcd.print(" ");
      lcd.print(power);
    } else {
      lcd.setCursor(11, 1);
      lcd.print(power);
    }

    lcd.print(" W");
    //  Serial.println(power);
  }
}

//----------------------- Read temperature ---------------------------
void ReadTemperature() {

  if (millis() - lastTempRequest >= delayInMillis) // waited long enough??
  {
    temperature = sensors.getTempCByIndex(0);
    idle = 0;
    sensors.requestTemperatures();
    delayInMillis = 750 / (1 << (12 - tempResolution));
    lastTempRequest = millis();
  }

  lcd.setCursor(0, 1);
  lcd.print(temperature, 1);
  lcd.print((char)223);

  idle++;

}
