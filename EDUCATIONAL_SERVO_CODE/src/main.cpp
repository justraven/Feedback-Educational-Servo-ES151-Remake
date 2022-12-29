/*
  EDUCATIONAL SERVO ES151
  CREATED BY : ALIM SATRIA F.W.K
  GITHUB : https://github.com/justraven
*/

/*
  note for mapping potentiometers (raw value)
  TACHO =
  SP    = 0 ~ 694
  KP    = 0 ~ 694
  KI    = 0 ~ 694
  KD    = 0 ~ 694
  DS    = 0 ~ 694*/

#define SYSTEM_USE_COMMA 1 // uncomment if your computer use ',' separator

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <parsing.h>

//----- define pins -----//
#define TACHO_PIN A1

#define SETPOINT_PIN A7
#define KP_PIN A5
#define KI_PIN A8
#define KD_PIN A6
#define DS_PIN A4

#define IN_L 7
#define IN_R 6
#define EN 5

//----- define PID parameter -----//
typedef struct
{

  float feedback = 0;
  float setPoint = 0;
  float KP = 0;
  float KI = 0;
  float KD = 0;
  int DS = 0; // data sampling, use for filter

  float KPValue = 0;
  float KIValue = 0;
  float KDValue = 0;

  float error = 0;
  float lastError = 0;

  float totalError = 0;
  float deltaError = 0;

  int maxControl = 255;
  int minControl = 0;

  int controlSignal = 0;

  // no time sampling setting, because loop period is fix. TS pin instead will be use for data sampling

} PIDParameters_t;

//----- define Moving Average filter parameter -----//
typedef struct
{

  float sum = 0;
  float average = 0;

} MovingAverageParameters_t;

//----- Parsing variable -----//
typedef struct
{

  float mode = 0; // mode selection, zero for using potentiometer, one for using LabView

  float setPoint = 0;

  float KP = 0;
  float KI = 0;
  float KD = 0;
  float DS = 0;

} ParsingVariable_t;

//----- call function -----//
PIDParameters_t parameter;
LiquidCrystal_I2C lcd(0x27, 20, 4);
MovingAverageParameters_t MA;
ParsingVariable_t parsing;

//----- define loop period -----//
unsigned long t = 0;
uint8_t loopPeriod = 50; // loop period is 50ms

//----- map float -----//
float mapFloat(float x, float inMin, float inMax, float outMin, float outMax)
{

  return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

//----- moving average filter -----//
float movingAverageFilter(uint8_t analogPin, int N)
{

  MA.sum = 0;

  for (int i = 0; i < N; i++)
    MA.sum += analogRead(analogPin);

  MA.average = MA.sum / N;

  return MA.average;
}

void setup()
{

  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();

  pinMode(IN_R, OUTPUT);
  pinMode(IN_L, OUTPUT);

  Serial.begin(115200);

  digitalWrite(IN_L, LOW);
  digitalWrite(IN_R, HIGH);
}

void loop()
{

  if(Serial.available() > 0)
  {

    READ_DATA_UNTIL('\n');
    data.replace(',', '.');
    parseString();

    parsing.mode = DATA_STR(0).toFloat();

    parsing.setPoint = DATA_STR(1).toFloat();
    parsing.KP = DATA_STR(2).toFloat();
    parsing.KI = DATA_STR(3).toFloat();
    parsing.KD = DATA_STR(4).toFloat();
    parsing.DS = DATA_STR(5).toFloat();

    Serial.flush();

  }

  if (millis() - t > loopPeriod)
  {

    t += loopPeriod;

    if (parsing.mode == 0)
    {
      parameter.setPoint = map(analogRead(SETPOINT_PIN), 0, 694, 0, 1023);
      constrain(parameter.setPoint, 0, 1023);
      parameter.KP = mapFloat(analogRead(KP_PIN), 0, 694, 0, 5);
      parameter.KI = mapFloat(analogRead(KI_PIN), 0, 694, 0, 1);
      parameter.KD = mapFloat(analogRead(KD_PIN), 0, 694, 0, 10);
      parameter.DS = map(analogRead(DS_PIN), 0, 694, 25, 150);
    }
    else if (parsing.mode == 1)
    {
      parameter.setPoint = parsing.setPoint;
      parameter.KP = parsing.KP;
      parameter.KI = parsing.KI;
      parameter.KD = parsing.KD;
      parameter.DS = parsing.DS;
    }

    parameter.feedback = movingAverageFilter(TACHO_PIN, 200);

    parameter.error = parameter.setPoint - parameter.feedback;
    parameter.totalError += parameter.error;

    if (parameter.totalError >= parameter.maxControl)
      parameter.totalError = parameter.maxControl;
    else if (parameter.totalError <= parameter.minControl)
      parameter.totalError = parameter.minControl;

    parameter.deltaError = parameter.error - parameter.lastError;

    parameter.KPValue = parameter.KP * parameter.error;
    parameter.KIValue = parameter.KI * parameter.totalError * loopPeriod;
    parameter.KDValue = (parameter.KD / loopPeriod) * parameter.deltaError;

    parameter.controlSignal = parameter.KPValue + parameter.KIValue + parameter.KDValue;

    if (parameter.controlSignal >= parameter.maxControl)
      parameter.controlSignal = parameter.maxControl;
    else if (parameter.controlSignal <= parameter.minControl)
      parameter.controlSignal = parameter.minControl;

    analogWrite(EN, parameter.controlSignal);

    parameter.lastError = parameter.error;

#ifdef SYSTEM_USE_COMMA

    String S = String(parameter.setPoint);
    String F = String(parameter.feedback);
    String P = String(parameter.KP);
    String I = String(parameter.KI);
    String D = String(parameter.KD);
    String T = String(parameter.DS);
    String O = String(parameter.controlSignal);

    S.replace('.', ',');
    F.replace('.', ',');
    P.replace('.', ',');
    I.replace('.', ',');
    D.replace('.', ',');
    T.replace('.', ',');
    O.replace('.', ',');

    Serial.println(
        'S' + S +
        'F' + F +
        'P' + P +
        'I' + I +
        'D' + D +
        'T' + T +
        'O' + O);

#else

    Serial.println(

        "S" + String(parameter.setPoint) +
        "F" + String(parameter.feedback) +
        "P" + String(parameter.KP) +
        "I" + String(parameter.KI) +
        "D" + String(parameter.KD) +
        "T" + String(parameter.DS) +
        "O" + String(parameter.controlSignal)

    );

#endif

    lcd.setCursor(0, 0);
    lcd.print("SP:");
    lcd.print(parameter.setPoint);
    lcd.setCursor(0, 1);
    lcd.print("PV:");
    lcd.print(parameter.feedback);
    // lcd.setCursor(0,2);
    // lcd.print("KP:");
    // lcd.print(parameter.KP);
    // lcd.setCursor(0,3);
    // lcd.print("KI:");
    // lcd.print(parameter.KI);
    // lcd.setCursor(11,0);
    // lcd.print("KD:");
    // lcd.print(parameter.KD);
    lcd.flush();
  }
}
