#include "series.hh"

#ifndef COMPUTE_ARITHMETIC_H
#define COMPUTE_ARITHMETIC_H
class ComputeArithmetic : public Series {
  //Constructor
  ComputeArithmetic() ;
  //Destructor
  ~ComputeArithmetic() = default;

  double computeTerm (Uint K) override;
};

#endif /* COMPUTE_ARITHMETIC_H */
