/* INCLUDES ********************************************************************/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <JC_Button.h>

/* DECLARATIONS *******************************************************************/
//LCD I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2);
// TEMPERATURE sensor data wire on the Arduino
#define ONE_WIRE_BUS 4

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
/********************************************************************/

const byte CurrentPin       = A4;         // current read pin
const byte VoltagePin       = A5;         // voltage read pin
//const byte voltageCheck     = A5;
//const byte PotInputPin      = A2;         // pot input
const byte RelayOnOff       = 12;
const byte ControlPin       = 13;          // control voltage pin
const byte FGenPin          = 5;
const byte StatusLED        = 6;          // On/Off LED

ToggleButton      // JC_button: define toggle buttons
  LoadOnOff(7),
  SetButton(8);
Button
  CursorToggle(9),
  ValueDown(10),
  ValueUp(11);

unsigned long previousMillisP = 0;
unsigned long currentMillisP;
unsigned long previousMillisA = 0;
unsigned long currentMillisA;
unsigned long previousMillisV = 0;
unsigned long currentMillisV;
unsigned long previousMillisT = 0;
unsigned long currentMillisT;
unsigned long previousMillis = 0;
unsigned long currentMillis;
int interval = 500;

//int potValue;
float current;
float voltage;
int power;

// Temperature settings
int  tempResolution           = 12;
unsigned long lastTempRequest = 0;
int  delayInMillis            = 0;
float temperature             = 0.0;
int  idle                     = 0;

// Shut-off Limits
float temperatureLimit        = 45.0;   // in Celsius
float currentLimit            = 2.0;    // in Amperes
float voltageLimit            = 12.0;   // in Volts
float powerLimit              = 80.0;   // in Watts
// Limits refs
float& currentLimitRef    = currentLimit;
float& voltageLimitRef    = voltageLimit;
float& tempLimitRef       = temperatureLimit;
float& powerLimitRef      = powerLimit;
// Limits screen positions
int    currentLimitPos[]  = {0,1,3,1};   // cursor start, row, printed value length, decimal places
int    voltageLimitPos[]  = {5,1,2,0};
int    powerLimitPos[]    = {9,1,2,0};
int    tempLimitPos[]     = {13,1,2,0};

// Transients
bool   TransientsStatus    = false;
float  transientFrequency  = 1;  // in Hz
float  transientMin        = 0.5; // in Amperes
float  transientMax        = 1.0; // in Amperes
// Transients refs
float& transientFrequencyRef = transientFrequency;
float& transientMinRef       = transientMin;
float& transientMaxRef       = transientMax;
// Transients screen positions
int    transientFrequencyPos[]  = {0,1,5,0};   // cursor start, row, printed value length, decimal places
int    transientMinPos[]        = {11,1,3,2};
int    transientMaxPos[]        = {11,0,3,2};

int controlVMin     = 0;
int controlVMax     = 0;
int controlMillis   = 0;
bool  controlStatus = false;

int CP  = 0;    // cursor position

float SetCurrentValue;
float CurrentVal1         = 1;    // set current 1.00 A value
float CurrentVal2         = 0;    // set current 0.10 A value
float CurrentVal3         = 0;    // set current 0.01 A value

int Load = 0;
int controlVoltage  = 0;
String Mode         = "Read";

int cycle = 0;
int cycleMax = 0;
float value; float valStep; float valMin; float valMax;

bool FGenStatus = false;

int test;
float diff;
float adjustment;
