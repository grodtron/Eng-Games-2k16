void state_normal(){
  Serial.println("doin nothing");
  motorLEFT->run(RELEASE);
  motorRIGHT->run(RELEASE);
}

