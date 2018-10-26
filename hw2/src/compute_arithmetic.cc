#include "compute_arithmetic.hh"


ComputeArithmetic::ComputeArithmetic():
  Series(){};

double ComputeArithmetic::computeTerm (Uint K) override{

  return 1.0 * K ;
}
