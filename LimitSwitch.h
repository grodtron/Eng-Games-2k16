class LimitSwitch {
  private:
    int pin;
  
  public:
    LimitSwitch(int pin)
      : pin(pin)
    {
      digitalWrite(pin, HIGH);  //turn on pull up resistor for flow sensor on pin 2
    }

    void setCallback(void (*isrFunc)(void)){
      attachInterrupt(digitalPinToInterrupt(pin), isrFunc, FALLING);//turn on interrupt for flow sensor on pin 2      
    }

};

