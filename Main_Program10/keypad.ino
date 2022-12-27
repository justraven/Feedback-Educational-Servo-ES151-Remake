void trial_but() {
  button = keypad.getKey();
  if (button != NO_KEY || key != NO_KEY) {
    lcd.clear();
    lcd.setCursor(3, 2);
    lcd.print(button);
  }
}

//
void coba_keypad() {
  keypad_but();
  if (button != NO_KEY || key != NO_KEY) {
    data3 = String(key);
    int score = data3.toInt();
    score1 = score - 48;
    data2 = String(score1);
    data += data2;
    score2 = data.toInt();
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(score2);
    lcd.setCursor(0, 2);
    lcd.print(data);
    if (button == '#') {
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("SAVED");
      while (button == '#') {}
      delay(700);
    }
  }
}

void score_keypad() {
  if (button != NO_KEY || key != NO_KEY) {
    data3 = String(key);
    int score = data3.toInt();
    score1 = score - 48;
    data2 = String(score1);
    data += data2;
    score2 = data.toInt();
    if (button == '#') {
      data = "";
      //      score2 = 0;
    }
  }
}

int score_keypad2(char value, String data4, int score3) {
  value = (int)keypad.getKey();
  if (value != NO_KEY) {
    data4 = String(value);
    int score = data3.toInt();
    score1 = score - 48;
    data2 = String(score1);
    data += data2;
    score3 = data.toInt();
    return score3;
//    if (button == '#') {
//      data = "";
//      score2 = 0;
//    }
  }
}
