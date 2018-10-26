#include "series.hh"

#ifndef COMPUTE_PI_H
#define COMPUTE_PI_H
class ComputePi : public Series {
public:
  //Constructor
  ComputePi();
  //Destructor
  virtual ~ComputePi() = default;

  double compute (int N) override ;

  double computeTerm (Uint K) override;

  double  getAnalyticPrediction() override;
};

#endif /* COMPUTE_PI_H */
