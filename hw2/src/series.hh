#include <iostream>



using Uint = unsigned int;

class Series{
public:
  //Constructor
  Series() ;
  //Destructor
  ~Series() = default;

  virtual double compute(Uint N) = 0;
  virtual double getAnalyticPrediction();
  void addTerm();
  virtual double computeTerm(Uint k) = 0;

private:
  int current_term  ;
  double current_value;

};
