#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { 'd', '#', '0', '*' },
  { 'c', '9', '8', '7' },
  { 'b', '6', '5', '4' },
  { 'a', '3', '2', '1' }
};

byte rowPins[ROWS] = { 52, 50, 48, 46 };  //pin untuk kontrol baris
byte colPins[COLS] = { 44, 42, 40, 38 };  //pin untuk kontrol kolom

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void keypad_but() {
  button = keypad.getKey();
  key = (int)button;
}

void buzz_on() {
  analogWrite(buzzer, 255);
  delay(100);
  analogWrite(buzzer, 0);
}

void buzz_long() {
  analogWrite(buzzer, 255);
  delay(100);
  analogWrite(buzzer, 0);
  delay(100);
  analogWrite(buzzer, 255);
  delay(2000);
  analogWrite(buzzer, 0);
}

void menu() {
MAIN:
  for (int i = 0; i >= 0; i++) {
    keypad_but();
    lcd.setCursor(5, 0);
    lcd.print("Main Menu");
    lcd.setCursor(0, 1);
    lcd.print("(A) Tunning PID");
    lcd.setCursor(0, 2);
    lcd.print("(B) Tunning LQR");
    lcd.setCursor(0, 3);
    lcd.print("(C) Run Motor");
    if (button == 'a') {
      delay(50);
      lcd.clear();
      buzz_on();
      for (int i = 0; i >= 0; i++) {
        keypad_but();
        lcd.setCursor(2, 0);
        lcd.print("Use the selector");
        lcd.setCursor(1, 2);
        lcd.print("Press '#' for OK");
        lcd.setCursor(1, 3);
        lcd.print("Press '*' -> CANCEL");
        if (button == '#') {
          lcd.clear();
          buzz_on();
          delay(100);
          goto PID;
        }
        if (button == '*') {
          lcd.clear();
          buzz_on();
          lcd.setCursor(3, 1);
          lcd.print("BACK TO MAIN");
          delay(700);
          lcd.clear();
          goto MAIN;
        }
      }
    }
    else if (button == 'b') {
      delay(50);
      lcd.clear();
      buzz_on();
      lcd.setCursor(2, 1);
      lcd.print("Use Keypad Only");
      delay(1200);
      lcd.clear();
      goto LQR;
    }
    else if (button == 'c') {
      delay(50);
      lcd.clear();
      buzz_on();
      for (int i = 0; i >= 0; i++) {
        keypad_but();
        lcd.setCursor(2, 0);
        lcd.print("Use the selector");
        lcd.setCursor(1, 2);
        lcd.print("Press '#' -> OK");
        lcd.setCursor(1, 3);
        lcd.print("Press '*' -> CANCEL");
        if (button == '#') {
          lcd.clear();
          buzz_on();
          delay(100);
          goto RUN;
        }
        if (button == '*') {
          lcd.clear();
          buzz_on();
          lcd.setCursor(3, 1);
          lcd.print("BACK TO MAIN");
          delay(700);
          lcd.clear();
          goto MAIN;
        }
      }
    }
    else {
      delay(50);
      goto MAIN;
    }
  }

PID:
  for (int i = 0; i >= 0; i++) {
    keypad_but();
    switch_pin();
    filter_pot();
    lcd.setCursor(0, 0);
    lcd.print("(A) Setpoint & TS");
    lcd.setCursor(0, 1);
    lcd.print("(B) P");
    lcd.setCursor(0, 2);
    lcd.print("(C) I");
    lcd.setCursor(0, 3);
    lcd.print("(D) D");

    if (button == '*') {
      lcd.clear();
      buzz_on();
      lcd.setCursor(3, 1);
      lcd.print("BACK TO MAIN");
      delay(700);
      lcd.clear();
      goto MAIN;
    }

    if (val_SEL1 == LOW) {
      if (button == 'a') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          lcd.setCursor(0, 1);
          lcd.print("Setpoint   : ");
          lcd_cl(13, 1, val_encs);
          lcd.setCursor(0, 2);
          lcd.print("T Sampling : ");
          lcd_cl(13, 2, val_times);
          if (button == '#') {
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      else if (button == 'b') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          lcd.setCursor(0, 1);
          lcd.print("P : ");
          lcd_cl(5, 1, val_pid[0]);
          if (button == '#') {
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      else if (button == 'c') {
        delay(50);
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          lcd.setCursor(0, 2);
          lcd.print("I : ");
          lcd_cl(5, 2, val_pid[1]);
          if (button == '#') {
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      else if (button == 'd') {
        delay(50);
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          lcd.setCursor(0, 3);
          lcd.print("D : ");
          lcd_cl(5, 3, val_pid[2]);
          if (button == '#') {
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      else if (button == '*') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          lcd.setCursor(4, 1);
          lcd.print("BACK TO MENU");
          delay(800);
          lcd.clear();
          goto MAIN;
        }
      }
    }

    else if (val_SEL2 == LOW) {
      lcd.clear();
      buzz_on();
      delay(100);
      buzz_on();
      for (int i = 0; i >= 0; i++) {
        keypad_but();
        kp = 3;
        ki = 0.1;
        kd = 1.2;
        sp = 90;  //Derajat
        lcd.setCursor(0, 0);
        lcd.print("Setpoint : ");
        lcd_cl(5, 0, sp);
        lcd.setCursor(0, 1);
        lcd.print("P : ");
        lcd_cl(5, 1, kp);
        lcd.setCursor(0, 2);
        lcd.print("I : ");
        lcd_cl(5, 2, ki);
        lcd.setCursor(0, 3);
        lcd.print("D : ");
        lcd_cl(5, 3, kd);
        if (button == '#') {
          lcd.clear();
          buzz_on();
          lcd.setCursor(2, 1);
          lcd.print("Default System");
          delay(700);
          lcd.clear();
          goto PID;
        }
      }
    }
    else if (val_SEL3 == LOW) {
      if (button == 'a') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          score_keypad();
          sp_key = score2;
          lcd.setCursor(0, 0);
          lcd.print("Setpoint : ");
          lcd.print(sp_key);
          if (button == '#') {
            sp_key = score2;
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      if (button == 'b') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          score_keypad();
          arr_key[0] = score2;
          lcd.setCursor(0, 1);
          lcd.print("P : ");
          lcd.print(arr_key[0]);
          if (button == '#') {
            arr_key[0] = score2;
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      if (button == 'c') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          score_keypad();
          arr_key[1] = score2;
          lcd.setCursor(0, 2);
          lcd.print("I : ");
          lcd.print(arr_key[1]);
          if (button == '#') {
            arr_key[1] = score2;
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
      if (button == 'd') {
        lcd.clear();
        buzz_on();
        for (int i = 0; i >= 0; i++) {
          filter_pot();
          keypad_but();
          score_keypad();
          arr_key[2] = score2;
          lcd.setCursor(0, 3);
          lcd.print("D : ");
          lcd.print(arr_key[2]);
          if (button == '#') {
            lcd.clear();
            buzz_on();
            lcd.setCursor(7, 1);
            lcd.print("SAVED");
            delay(700);
            lcd.clear();
            goto PID;
          }
        }
      }
    }
  }

LQR:
  for (int i = 0; i >= 0; i++) {
    keypad_but();
    switch_pin();
    filter_pot();
    lcd.setCursor(0, 0);
    lcd.print("Maap masih belum bisa !");
    lcd.setCursor(0, 2);
    lcd.print("Tekan * untuk kembali");
    if (button == '*') {
      lcd.clear();
      buzz_on();
      lcd.setCursor(3, 1);
      lcd.print("BACK TO MAIN");
      delay(700);
      lcd.clear();
      goto MAIN;
    }
    //    lcd.print("(A) Matrix Q");
    //    lcd.setCursor(0, 2);
    //    lcd.print("(B) Value R");

    //    if (val_SEL3 == LOW) {
    //      lcd.clear();
    //      buzz_on();
    //      if (button == 'a') {
    //        for (int i = 0; i >= 0; i++) {
    //          keypad_but();
    //          score_keypad();
    //          for (int k = 0; k < 3; k++) {
    //            for (int l = 0; l < 3; l++) {
    //              matrix_Q[k][l] = score2;
    //              matrix_Qn[k][l] = matrix_Q[k][l];
    //              for (int a = 7; a < 16; a += 4) {
    //                int b = 0;
    //                if (a > 16) {
    //                  b += 1;
    //                }
    //                lcd.setCursor(a, b);
    //                lcd.print(matrix_Qn[k][l]);
    //              }
    //            }
    //          }
    //          lcd.setCursor(0, 0);
    //          lcd.print("Q = ");
    //          lcd.print("| ");
    //          lcd.setCursor(6, 1);
    //          lcd.print("|");
    //          lcd.setCursor(17, 1);
    //          lcd.print("|");
    //          lcd.setCursor(6, 2);
    //          lcd.print("|");
    //          lcd.setCursor(17, 2);
    //          lcd.print("|");
    //          if (button == '#') {
    //            //            R = score2;
    //            lcd.clear();
    //            buzz_on();
    //            lcd.setCursor(7, 1);
    //            lcd.print("SAVED");
    //            delay(700);
    //            lcd.clear();
    //            goto LQR;
    //          }
    //        }
    //      }
    //      if (button == 'b') {
    //        lcd.clear();
    //        buzz_on();
    //        for (int i = 0; i >= 0; i++) {
    //          filter_pot();
    //          keypad_but();
    //          score_keypad();
    //          R = score2;
    //          lcd.setCursor(0, 1);
    //          lcd.print("R : ");
    //          lcd.print(R);
    //          if (button == '#') {
    //            R = score2;
    //            lcd.clear();
    //            buzz_on();
    //            lcd.setCursor(7, 1);
    //            lcd.print("SAVED");
    //            delay(700);
    //            lcd.clear();
    //            goto LQR;
    //          }
    //        }
    //      }
    //    }
    //    else {
    //      lcd.clear();
    //      buzz_on();
    //      delay(80);
    //      buzz_on();
    //      delay(800);
    //    }
  }

RUN:
  for (int i = 0; i >= 0; i++) {
    keypad_but();
    lcd.setCursor(3, 0);
    lcd.print("Choose Sensor");
    lcd.setCursor(0, 1);
    lcd.print("(A) Potensiometer");
    lcd.setCursor(0, 2);
    lcd.print("(B) Tacho Generator");
    lcd.setCursor(0, 3);
    lcd.print("(C) Encoder");
    if (button == '*') {
      lcd.clear();
      buzz_on();
      lcd.setCursor(3, 1);
      lcd.print("BACK TO MAIN");
      delay(700);
      lcd.clear();
      goto MAIN;
    }

    if (button == 'a') {
      delay(50);
      lcd.clear();
      buzz_on();
      for (int i = 0; i >= 0; i++) {
        switch_pin();
        if (val_SEL1 == LOW) {
          for (int i = 0; i >= 0; i++) {
            filter_pot();
            keypad_but();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Potensio Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd_cl(9, 1, val_encs);
            lcd.setCursor(0, 2);
            lcd.print("Real   : ");
            lcd_cl(9, 2, val_encp);
            lcd.setCursor(0, 3);
            lcd.print("Error  : ");
            lcd_cl(9, 3, error);

            PID_position(val_encp, val_encs, val_pid[0], val_pid[1], val_pid[2]);
            RunMotor();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(100);
              goto MAIN;
            }
          }
        }
        if (val_SEL2 == LOW) {
          for (int i = 0; i >= 0; i++) {
            filter_pot();
            keypad_but();
            kp = 10;
            ki = 1.8;
            kd = 0.8;
            sp = 150;
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Default Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd_cl(9, 1, val_encs);
            lcd.setCursor(0, 2);
            lcd.print("Real   : ");
            lcd_cl(9, 2, val_encp);
            lcd.setCursor(0, 3);
            lcd.print("Error  : ");
            lcd_cl(9, 3, error);

            PID_position(val_encp, val_encs, kp, ki, kd);
            RunMotor();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(200);
              goto MAIN;
            }
          }
        }
        if (val_SEL3 == LOW) {
          for (int i = 0; i >= 0; i++) {
            keypad_but();
            filter_pot();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Keypad Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd.print(sp_key);
            lcd.setCursor(0, 2);
            lcd.print("Real : ");
            lcd.print(val_encp);
            lcd.setCursor(0, 3);
            lcd.print("Error : ");
            lcd.print(error);
            PID_position(val_encp, sp_key, arr_key[0], arr_key[1], arr_key[2]);
            RunMotor();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(200);
              goto MAIN;
            }
          }
        }
      }
    }
    else if (button == 'b') {
      delay(50);
      lcd.clear();
      buzz_on();
      for (int i = 0; i >= 0; i++) {
        switch_pin();
        if (val_SEL1 == LOW) {
          for (int i = 0; i >= 0; i++) {
            filter_pot();
            keypad_but();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Potensio Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd_cl(9, 1, val_encs_y);
            lcd.setCursor(0, 2);
            lcd.print("Tacho  : ");
            lcd_cl(9, 2, val_tacho_cw_z);
            lcd.setCursor(0, 3);
            lcd.print("Error  : ");
            lcd_cl(9, 3, error);

            PID_position(val_tacho_cw_z, val_encs_y, val_pid[0], val_pid[1], val_pid[2]);
            RunSpeed();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(100);
              goto MAIN;
            }
          }
        }
        if (val_SEL2 == LOW) {
          for (int i = 0; i >= 0; i++) {
            filter_pot();
            keypad_but();
            kp = 10;
            ki = 1.8;
            kd = 0.8;
            sp = 150;
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Default Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd_cl(9, 1, sp);
            lcd.setCursor(0, 2);
            lcd.print("Real   : ");
            lcd_cl(9, 2, val_tacho_cw);
            lcd.setCursor(0, 3);
            lcd.print("Error  : ");
            lcd_cl(9, 3, error);
            PID_position(val_tacho_cw, sp, kp, ki, kd);
            RunSpeed();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(200);
              goto MAIN;
            }
          }
        }
        if (val_SEL3 == LOW) {
          for (int i = 0; i >= 0; i++) {
            keypad_but();
            filter_pot();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Keypad Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd.print(sp_key);
            lcd.setCursor(0, 2);
            lcd.print("Real : ");
            lcd.print(val_tacho_cw);
            lcd.setCursor(0, 3);
            lcd.print("Error : ");
            lcd_cl(9, 3, error);
            PID_position(val_tacho_cw, sp_key, arr_key[0], arr_key[1], arr_key[2]);
            RunSpeed();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(200);
              goto MAIN;
            }
          }
        }
      }
    }
    else if (button == 'c') {
      delay(50);
      lcd.clear();
      buzz_on();
      for (int i = 0; i >= 0; i++) {
        switch_pin();
        if (val_SEL1 == LOW) {
          for (int i = 0; i >= 0; i++) {
            filter_pot();
            keypad_but();
            rpm_val();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Potensio Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd_cl(9, 1, val_encs);
            lcd.setCursor(0, 2);
            lcd.print("Enc    : ");
            lcd_cl(9, 2, rpm);
            lcd.setCursor(0, 3);
            lcd.print("Error  : ");
            lcd_cl(9, 3, error);
            PID_position(rpm, val_encs, val_pid[0], val_pid[1], val_pid[2]);

            RunSpeed_enc();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(100);
              goto MAIN;
            }
          }
        }
        if (val_SEL2 == LOW) {
          for (int i = 0; i >= 0; i++) {
            filter_pot();
            keypad_but();
            kp = 10;
            ki = 1.8;
            kd = 0.8;
            sp = 150;
            rpm_val();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Default Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd.print(sp);
            lcd.setCursor(0, 2);
            lcd.print("Real : ");
            lcd.print(counter);
            lcd.setCursor(0, 3);
            lcd.print("Error : ");
            lcd.print(error);
            PID_position(rpm, val_encs, kp, ki, kd);
            RunEnc();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(200);
              goto MAIN;
            }
          }
        }
        if (val_SEL3 == LOW) {
          for (int i = 0; i >= 0; i++) {
            keypad_but();
            filter_pot();
            rpm_val();
            send_to_python();
            lcd.setCursor(3, 0);
            lcd.print("Keypad Value");
            lcd.setCursor(0, 1);
            lcd.print("Target : ");
            lcd.print(sp_key);
            lcd.setCursor(0, 2);
            lcd.print("Real : ");
            lcd.print(counter);
            lcd.setCursor(0, 3);
            lcd.print("Error : ");
            lcd.print(error);
            PID_position(rpm, sp_key, arr_key[0], arr_key[1], arr_key[2]);
            RunEnc();
            if (button == '*') {
              buzz_long();
              lcd.clear();
              stop_();
              delay(200);
              goto MAIN;
            }
          }
        }
      }
    }
    else {
      delay(50);
      goto RUN;
    }
  }
}
