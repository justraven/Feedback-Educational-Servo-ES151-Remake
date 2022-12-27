void coba_lcd() {
  lcd.setCursor(0, 0);
  lcd.print("-------------");
}

void lcd_tacho_debug() {
  //  rpm_val();
  lcd.setCursor(0, 0);
  lcd.print("tacho_cw : ");
  lcd.print(val_tacho_cw);
  lcd.setCursor(0, 1);
  lcd.print("Encoder : ");
  lcd.print(counter);
  lcd.setCursor(0, 2);
  lcd.print("Target : ");
  lcd_cl(9, 2, val_encs);
  lcd.setCursor(0, 3);
  lcd.print("Real : ");
  lcd.print(val_encp);
}

void lcd_cl(int column, int row, int val) {
  lcd.setCursor(column, row);
  lcd.print("    ");
  lcd.setCursor(column, row);
  lcd.print(val);
}

void lcd_pid_debug() {
  lcd.setCursor(0, 0);
  lcd.print("P : ");
  lcd.println(val_pid[0]);
  lcd.setCursor(0, 1);
  lcd.print("I : ");
  lcd.println(val_pid[1]);
  lcd.setCursor(0, 2);
  lcd.print("D : ");
  lcd.println(val_pid[2]);
  lcd.setCursor(0, 3);
  lcd.print("Time_S : ");
  lcd.println(val_times);
}

void pin_debug() {
  Serial.print("tacho_cw : "); Serial.println(val_tacho_cw);
  delay(500);
  Serial.print("tacho_ccw : "); Serial.println(val_tacho_ccw);
  delay(500);
  Serial.print("enc pot : "); Serial.println(val_encp); delay(500);
  Serial.print("enc set : "); Serial.println(val_encs); delay(500);
  Serial.print("P : "); Serial.println(val_pid[0]); delay(500);
  Serial.print("I : "); Serial.println(val_pid[1]); delay(500);
  Serial.print("D : "); Serial.println(val_pid[2]); delay(500);
}

void lcd_pid() {
  switch_pin();
  filter_pot();
  keypad_but();
  if (val_SEL1 == LOW) {
    lcd.setCursor(4, 0);
    lcd.print("Potensiometer");
    lcd.setCursor(0, 1);
    lcd.print("P : ");
    lcd.print(arr_SEL1[0]);
    lcd.setCursor(0, 2);
    lcd.print("I : ");
    lcd.print(arr_SEL1[1]);
    lcd.setCursor(0, 3);
    lcd.print("D : ");
    lcd.print(arr_SEL1[2]);
  }
  if (val_SEL2 == LOW) {
    lcd.setCursor(6, 0);
    lcd.print("Default");
    lcd.setCursor(0, 1);
    lcd.print("P : ");
    lcd.print(arr_SEL2[0]);
    lcd.setCursor(0, 2);
    lcd.print("I : ");
    lcd.print(arr_SEL2[1]);
    lcd.setCursor(0, 3);
    lcd.print("D : ");
    lcd.print(arr_SEL2[2]);
  }
  if (val_SEL3 == LOW) {
    lcd.setCursor(6, 0);
    lcd.print("Keypad");
    lcd.setCursor(0, 1);
    lcd.print("P : ");
    lcd.print(arr_key[0]);
    lcd.setCursor(0, 2);
    lcd.print("I : ");
    lcd.print(arr_key[1]);
    lcd.setCursor(0, 3);
    lcd.print("D : ");
    lcd.print(arr_key[2]);
  }
}
