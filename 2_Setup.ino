void setup(void)
{
  lcd.begin();                //Initializing display
  lcd.backlight();            //To Power ON the back light
  Serial.begin(9600);         // start serial port

  // JC_button: begin monitoring buttons
  LoadOnOff.begin();
  SetButton.begin();
  CursorToggle.begin();
  ValueDown.begin();
  ValueUp.begin();

  LoadOff();
  SetLimits();

  //  Temperature sensor
  sensors.begin();            // Start up the temperature sensor library
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  delayInMillis = 1000 / (1 << (12 - tempResolution));
  lastTempRequest = millis();


  pinMode(FGenPin, OUTPUT);
  pinMode(ControlPin, OUTPUT);
  //  potValue = analogRead(PotInputPin);

}
