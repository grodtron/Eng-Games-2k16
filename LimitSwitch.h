// Uncomment to use interrupt-based non-debouncing version
//#define LIMIT_INTERRUPT

class LimitSwitch {
  private:
    int pin;
    #ifdef LIMIT_INTERRUPT
    #else
      void (*callback)(void);
      int downCount;
    #endif

  
  public:
    LimitSwitch(int pin)
      : pin(pin)
      #ifdef LIMIT_INTERRUPT
      #else
        , callback(NULL)
        , downCount(0)
      #endif
    {
      pinMode(pin, INPUT);
      digitalWrite(pin, HIGH);
    }

    void setCallback(void (*isrFunc)(void)){
      #ifdef LIMIT_INTERRUPT
        attachInterrupt(digitalPinToInterrupt(pin), isrFunc, FALLING);//turn on interrupt for flow sensor on pin 2
      #else
        callback = isrFunc;
      #endif
    }

    void update(){
      #ifdef LIMIT_INTERRUPT
      #else
        if(! digitalRead(pin)){
          downCount += 1;
          if(callback && downCount >= 10){
            callback();
            downCount = 0;
          }
        }else{
          downCount = 0;
        }
      #endif
      
    }

};

