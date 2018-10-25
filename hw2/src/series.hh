#include <iostream>



using Uint = unsigned int;

class Series{
public:
  //Constructor
  Series();
  //Destructor
  ~Series();

  virtual double compute(Uint N) = 0;

private:
  int current_term {0};
  double current_value {0.};

};
