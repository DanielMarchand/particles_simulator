#include "series.hh"

#ifndef COMPUTE_PI_H
#define COMPUTE_PI_H
class ComputePi : public Series {
  //Constructor
  ComputePi();
  //Destructor
  virtual ~ComputePi() = default;

  double compute (Uint N) override ;

  double computeTerm (Uint K) override;

  double  getAnalyticPrediction() override;
};

#endif /* COMPUTE_PI_H */
