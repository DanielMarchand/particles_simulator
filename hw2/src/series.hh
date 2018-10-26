#include <iostream>


#ifndef SERIES_H
#define SERIES_H
using Uint = unsigned int;

class Series{
public:
  //Constructor
  Series() ;
  //Destructor
  virtual ~Series() = default;

  void addTerm();
  virtual double compute(Uint N);
  virtual double getAnalyticPrediction();
  virtual double computeTerm(Uint k) = 0;

protected:
  int current_term  ;
  double current_value;

};

#endif /* SERIES_H */
