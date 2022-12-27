#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define EN 5
#define IN1 6
#define IN2 7

//*** Uncomment the statement below according to the name of your group member ***//
#define Rafief
//#define Sidik
//#define Abidin

const int encoderPinA = 2;
const int encoderPinB = 3;

const int PPR = 12;
const int gearRatio = 64;
const int decodeNumber = 4;
double rotate = 0.0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
volatile int counter = 0;
unsigned int rpm;
unsigned long timeold;

int tacho_cw = A1;
int tacho_ccw = A0;
int enc_pot = A2;
int enc_set = A7;

float pin_pid[3] = {A5, A8, A6};
int time_s = A4;
int buzzer = A9;

#define SEL1 34
#define SEL2 32
#define SEL3 30

int matrix_Q[4][4], matrix_Qn[4][4], R;

float kontrol;
char button;
int val_encs1;
int key;
int sp_key;
int sp_key1;
int sp_key2;
int propo1;
String data = "";
String data2 = "";
String data3 = "";
int score;
int score1;
int score2;

int val_tacho_cw, val_tacho_cwn, val_tacho_ccw, val_encp, val_encs, val_times_n, val_times;
int val_pid[3], val_pot_n[3], arr_SEL1[3], arr_SEL2[3], arr_key[3];
int val_tacho_n, val_tacho_n1, val_encp_n, val_encs_n;
int val_SEL1, val_SEL2, val_SEL3;
int val_encs_tacho, val_encs_t, val_encs_ta;
int val_tacho_cw_y, val_tacho_cw_z, val_tacho_cw_b;
int val_encs_y, val_encs_z, val_encs_b;

float kp;
float ki;
float kd;
int sp;
int val;
float error = 0;
float last_error = 0;
float integral = 0;
float derivative;
unsigned long timelast;
float previousTime = 0;           //for calculating delta t
float previousError = 0;          //for calculating the error derivative
float errorIntegral = 0;          //for calc error integal
float currentTime = 0;            //time in the moment of calculation
float deltaTime = 0;
float controlSignal = 0;
int motorDirection = 0;
int PWMValue = 0;
int rpm_;

String conv[3] = "";
int num[3];

float EMA_a = 0.1;

void setup() {
  Serial.begin(9600);
  //  TCCR0B = TCCR0B & B11111000 | B00000001;
  //  setPwmFrequency(5, 1);
  //  TCCR0B = TCCR0B & B11111000 | B00000010;
  setPwmFrequency(5, 1);
  lcd.begin(20, 4);
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(SEL1, INPUT_PULLUP);
  pinMode(SEL2, INPUT_PULLUP);
  pinMode(SEL3, INPUT_PULLUP);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  lastStateCLK = digitalRead(encoderPinA);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

  //  val_pin_setup();
  //  previousMillis = millis();
  counter = 0;
  rpm = 0;
  timeold = 0;

  lcd.init();
  lcd.backlight();

  //  lcd.setCursor(4, 0);
  //  lcd.print("Lab Otomasi");
  //  delay(1000);
  //  lcd.clear();
  //  lcd.setCursor(0, 1);
  //  lcd.print("Feedback Educational");
  //  lcd.setCursor(0, 2);
  //  lcd.print("Servo ES151 (Remake)");
  //  delay(1800);
  //  lcd.clear();
  //  lcd.setCursor(5, 3);
  //  lcd.print("TRIK 2020");
  //  delay(1000);
  //  lcd.clear();
}

void loop() {
  //// Uncomment below if you want potensio without filter
  //  val_pin_setup();

  //// Uncomment below and val_pin_setup on the void setup if you want potensio with filter
  //  filter_pot();
  //  send_to_python();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Target  : ");
  //  lcd_cl(10, 0, val_encs);

  //  val_encs_b = map(val_encs, 0, 360, 40, 262);
  //    enc_debug();
  //  PID_encoder();

  /// -- LCD and Serial Debug --
  //    val_tacho = analogRead(A0);
  //  val_tacho_n = analogRead(tacho_cw);
  //  val_tacho_cw = (EMA_a * val_tacho_n) + ((1 - EMA_a) * val_tacho_cw);
  //  int val_tacho_cw_y = map(val_tacho_cw, 0, 1023, 280, 980);
  //  int val_tacho_cw_z = map(val_tacho_cw_y, 280, 980, 40, 75);
  //  int val_tacho_cw_b = map(val_tacho_cw_z, 40, 75, 0, 300);
  //
  //  val_encs_t = analogRead(enc_set);
  //  val_encs_t = map(val_encs_t, 0, 671, 0, 360);
  //  val_encs_t = poten_filter(val_encs_t, 336);
  //  val_encs_y = map(val_encs_t, 0, 360, 40, 75);
  //  int val_encs_z = map(val_encs_y, 40, 75, 0, 30);
  //  int val_encs_b = map(val_encs_y, 40, 75, 0, 300);
  //  //  val_encs_b = (EMA_a * val_encs_z) + ((1 - EMA_a) * val_encs_b);
  //
  //  for (int i = 0; i < 3; i++) {
  //    val_pid[i] = map(val_pid[i], 0, 671, 0, 100) * 0.1;
  //  }
  //
  //  //  lcd_tacho_debug();
  //  lcd.setCursor(0, 0);
  //  lcd.print("tacho_cw : ");
  //  lcd_cl(12, 0, val_tacho_cw_b);
  //
  //  lcd.setCursor(0, 2);
  //  lcd.print("Target   : ");
  //  lcd_cl(12, 2, val_encs_b);
  //
  //  lcd.setCursor(0, 3);
  //  lcd.print("Error    : ");
  //  lcd_cl(12, 3, error);
  //
  //  //  motor_cw(val_encs_y);
  //  PID_position(val_tacho_cw_z, val_encs_y, val_pid[0], val_pid[1], val_pid[2]);
  //  RunSpeed();
  //  lcd_pid_debug();
  //  pin_debug();
  //  lcd_pid();
  //  lcd.setCursor(0, 1);
  //  lcd.print("Target   : ");
  //  lcd_cl(11, 1, val_encs);
  //  val_encs_ta = map(val_encs_tacho, 0, 168, 0, 360);
  //  lcd.setCursor(0, 2);
  //  lcd.print("Tacho_Sp : ");
  //  lcd_cl(11, 2, val_encs_ta);
  //  val_tacho_cwn = map(val_tacho_cw, 0, 235, 0, 360);
  //  lcd.setCursor(0, 3);
  //  lcd.print("Tacho    : ");
  //  lcd_cl(11, 3, val_tacho_cwn);

  /// -- Switch Pin --
  //  switch_pin();

  //// -- Menu --
  menu();
  //  lcd.setCursor(2, 0);
  //  lcd.print("------------------");
  //  lcd.setCursor(2, 1);
  //  lcd.print("|  ");
  //  lcd.print("P : ");
  //  lcd.print(val_pid[0]);
  //  lcd.setCursor(17, 1);
  //  lcd.print("|");
  //  lcd.setCursor(2, 2);
  //  lcd.print("|  ");
  //  lcd.setCursor(17, 2);
  //  lcd.print("|");
  //  lcd.setCursor(2, 3);
  //  lcd.print("------------------");

  //    if (val_SEL1 == LOW) {
  //      lcd.setCursor(4, 0);
  //      lcd.print("Potensiometer");
  //    }
  //    if (val_SEL2 == LOW) {
  //      lcd.setCursor(6, 0);
  //      lcd.print("Default");
  //    }
  //    if (val_SEL3 == LOW) {
  //      lcd.setCursor(6, 0);
  //      lcd.print("Keypad");
  //    }

  //// -- Motor Moving --
  //  PID_tacho();
  //  val_encs_b = map(val_encs_tacho, 0, 175, 40, 175);
  //  delay(3000);
  //  stop_();
  //  delay(1000);
  //  motor_ccw(200);
  //  delay(3000);
  //  stop_();
  //  delay(1000);

  //  enc_debug();
  //
  //  PID_encoder();

  //// -- Encoder Tacho --
  //  tacho_enc();

  // -- Encoder Default --
  //  def_enc();

  //// -- Encoder Potensio --
  //  pot_enc();

  //// -- Encoder Motor -- Choose Just One
  //  enc_motor();
  //  enc_interupt();

  //// -- Keypad Button --
  //   keypad_but();
  //   coba_keypad();
  //   trial_but();
  //
  //      PID_tacho();
  //    lcd.setCursor(1, 1);
  //    lcd.print("Tacho : ");
  //    lcd.print(val_tacho_cw);
  //
  //    lcd.setCursor(1, 2);
  //    lcd.print("Setpoint : ");
  //    lcd.println(val_encs);
  //
  //    lcd.setCursor(1, 3);
  //    lcd.print("Error : ");
  //    lcd.println(error);

  //// -- Coba Encoder PID --
  //    PID_position(counter, val_encs, val_pid[0], val_pid[1], val_pid[2]);
  //    RunMotor();
  //  lcd.setCursor(0, 1);
  //  lcd.print("Encoder : ");
  //  lcd.print(counter);
  //  lcd.setCursor(0, 2);
  //  lcd.print("Setpoint : ");
  //  lcd.print(val_encs);
  //  lcd.setCursor(0, 3);
  //  lcd.print("RPM : ");
  //  lcd.print(rpm);
  //  lcd.setCursor(0,0);
  //  lcd.print("nilai : ");
}
