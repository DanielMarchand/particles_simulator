#include "series.hh"
#include <math.h>

#ifndef COMPUTE_ARITHMETIC_H
#define COMPUTE_ARITHMETIC_H
class ComputeArithmetic : public Series {
public:
  //Constructor
  ComputeArithmetic() ;
  //Destructor
  virtual ~ComputeArithmetic() = default;

  double computeTerm (Uint K) override;
};

#endif /* COMPUTE_ARITHMETIC_H */
