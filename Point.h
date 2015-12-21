#ifndef POINT_H_
#define POINT_H_

#include <math.h>

struct Point {
  public:
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    void print_self(const char * name){
      Debug.print(name);
      Debug.print(" (");
      Debug.print(x);
      Debug.print(", ");
      Debug.print(y);
      Debug.println(")");
    }

    int magnitude(){
      return hypot(x, y);
    }
    
};

#endif
