#include <iostream>


#ifndef SERIES_H
#define SERIES_H
// long unsigned int is utilized so the program is able to perform
// iterations beyond 65535
using Uint = long unsigned int;

class Series{
public:
  //Constructor
  Series(std::string first_line_inp);
  //Destructor
  virtual ~Series() = default;

  void addTerm();
  virtual double compute(int N);
  virtual double getAnalyticPrediction();
  virtual double computeTerm(Uint k) = 0;
  virtual std::string getFirstLine();

protected:
  int current_term  ;
  double current_value;
  std::string first_line;

};

#endif /* SERIES_H */
