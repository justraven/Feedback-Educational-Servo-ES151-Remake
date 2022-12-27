void PID_position(float val, int target, int kp, int ki, int kd) {
  currentTime = micros();
  deltaTime = (currentTime - previousTime) / 1000000.0;
  previousTime = currentTime;

  error = target - val;
  integral = error + last_error;
  derivative = (error - last_error);
  controlSignal = ((kp * error) + (ki * integral) + (kd * (derivative)));
  last_error = error;
}


void PID_keypad() {
  filter_pot();
  keypad_but();
  score_keypad();
  PID_position(val_encp, sp_key, arr_key[0], arr_key[1], arr_key[2]);
  RunMotor();
}

void PID_encoder() {
  filter_pot();
  PID_position(rpm, val_encs_b, val_pid[0], val_pid[1], val_pid[2]);
  RunEnc();
}

void PID_tacho() {
  filter_pot();
  val_encs_b = map(val_encs_tacho, 0, 165, 40, 165);
  PID_position(val_tacho_cw, val_encs_b, val_pid[0], val_pid[1], val_pid[2]);
  RunSpeed();
}
