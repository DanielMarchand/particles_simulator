#include "compute_arithmetic.hh"
#include "series.hh"

ComputeArithmetic::ComputeArithmetic():
  Series("The Artihemtic Series:"){
}

/*---------------------------------------------------------------*/
double ComputeArithmetic::computeTerm (Uint K) {

  return 1.0 * K ;
}
