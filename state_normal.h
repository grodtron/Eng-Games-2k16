void state_normal(){
  Serial.println("doin nothing");
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}

