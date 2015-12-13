class Brushless {

  private:
    int pin;

    const static int THROTTLE_MIN = 130;
    const static int THROTTLE_MAX = 255;

  public:
    Brushless(int pin)
      :pin(pin)
    {
    }

    void init(){
      pinMode(pin, OUTPUT);
      analogWrite(pin, THROTTLE_MIN);
    }

    void setThrottle(int throttle){
      analogWrite(pin, map(throttle,
        0,            255,
        THROTTLE_MIN, THROTTLE_MAX));
    }

};

