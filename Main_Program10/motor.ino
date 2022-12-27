void motor_cw(int nilai) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN, nilai);
}

void motor_cw_tacho(int nilai) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  if (nilai < 40) {
    nilai = 40;
  }
  analogWrite(EN, nilai);
}

void motor_ccw(int nilai) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN, nilai);
}

void stop_() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 0);
}

void RunMotor() {
  //Speed
  PWMValue = (int)fabs(controlSignal);    //PWM values cannot be negative and have to be integers
  if (PWMValue > 235) {
    PWMValue = 235;                       //capping the PWM signal
  }
  if (PWMValue < 50 && error != 0) {
    PWMValue = 50;
  }
  if (error < 3 && error > -3) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    PWMValue = 0;
  }

  //set the direction
  if (controlSignal < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    if (val_encp > 300 && error < -200) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
  }
  else if (controlSignal > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    if (val_encp < 60 && error > 200) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    PWMValue = 0;
  }
  analogWrite(EN, PWMValue);
}

void RunEnc() {
  //Speed
  PWMValue = (int)fabs(controlSignal);    //PWM values cannot be negative and have to be integers
  if (PWMValue > 255) {
    PWMValue = 255;                       //capping the PWM signal
  }
  if (PWMValue < 50 && error != 0) {
    PWMValue = 50;
  }

  //set the direction
  if (controlSignal < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else if (controlSignal > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    PWMValue = 0;
  }
  analogWrite(EN, PWMValue);
}

void RunSpeed() {
  PWMValue = (int)fabs(controlSignal);    //PWM values cannot be negative and have to be integers
  //  if (PWMValue > 75) {
  //    PWMValue = 75;                       //capping the PWM signal
  //  }
  if (PWMValue < 40) {
    PWMValue = 40;
  }
  if (val_encs_y < 43 && error < -20) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    PWMValue = 0;
  }
  else if (val_encs_y >= 43) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  //  digitalWrite(IN1, HIGH);
  //  digitalWrite(IN2, LOW);
  analogWrite(EN, PWMValue);
}

void RunSpeed_enc() {
  PWMValue = (int)fabs(controlSignal);    //PWM values cannot be negative and have to be integers
  if (PWMValue < 35) {
    PWMValue = 35;
  }
  if (val_encs < 50 && error < -150) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    PWMValue = 40;
  }
  else if (val_encs >= 50) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  analogWrite(EN, PWMValue);
}
