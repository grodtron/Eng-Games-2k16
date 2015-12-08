struct Point {
  public:
    const int x;
    const int y;
    Point(int x, int y) : x(x), y(y) {}

    void print_self(const char * name){
      Serial.print(name);
      Serial.print(" (");
      Serial.print(x);
      Serial.print(", ");
      Serial.print(y);
      Serial.println(")");
    }
    
};

