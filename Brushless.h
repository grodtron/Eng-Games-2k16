class Brushless {

  private:
    int pin;
    bool on;

    const static int THROTTLE_MIN = 130;
    const static int THROTTLE_MAX = 255;

  public:
    Brushless(int pin)
      :pin(pin), on(false)
    {
    }

    void init(){
      pinMode(pin, OUTPUT);
      analogWrite(pin, THROTTLE_MIN);
    }

    void setThrottle(int throttle){
      on = throttle > 0;
      analogWrite(pin, map(throttle,
        0,            255,
        THROTTLE_MIN, THROTTLE_MAX));
    }

    bool isOn(){
      return on;
    }

};

