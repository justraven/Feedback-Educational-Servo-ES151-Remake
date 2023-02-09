//void enc_motor() {
//  if (millis() - timelast >= 1000) {
//    timelast = millis();
//    rpm_ = ((counter * 60) / 120) * 10;
//    rpm_ = map(rpm_, 900, 3010, 1050, 2350);
//  }
//}

void updateEncoder() {
  currentStateCLK = digitalRead(encoderPinA);
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    if (digitalRead(encoderPinB) != currentStateCLK) {
      counter --;
    } else {
      counter ++;
    }
  }
  lastStateCLK = currentStateCLK;
}


void rpm_val() {
  if (millis() - timelast >= 100) {
    timelast = millis();
    rpm_ = ((counter * 60) / 380);
    rpm = (EMA_a * rpm_) + ((1 - EMA_a) * rpm);
  }
  counter = 0;
}

void count_val(){
  rpm = (counter*10) /50;
  counter = 0;
}

void enc_debug() {
  rpm_val();
  filter_pot();
  Serial.print("Counter: ");
  Serial.print(counter);
  lcd.setCursor(0, 0);
  lcd.print("Target  : ");
  lcd_cl(10, 0, val_encs_b);
  lcd.setCursor(0, 1);
  lcd.print("Counter : ");
  lcd_cl(10, 1, counter);
  lcd.setCursor(0, 2);
  lcd.print("RPM     : ");
  lcd_cl(10, 2, rpm);
  lcd.setCursor(0, 3);
  lcd.print("Error   : ");
  lcd_cl(10, 3, error);
//  lcd.print("Tacho   : ");
//  lcd_cl(10, 3, val_tacho_cw);
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

//void enc_interupt() {
//  rotate = (360 * counter) / (PPR * decodeNumber * gearRatio);
//  counter = rotate;
//  if (counter == previous_counter) {
//    counter = 0;
//  }
//  lcd.setCursor(2, 1);
//  lcd.print(counter);
//  Serial.print("Encoder : ");
//  Serial.println(counter);
//  previous_counter = counter;
//}
