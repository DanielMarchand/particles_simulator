#include "compute_arithmetic.hh"
#include "series.hh"

ComputeArithmetic::ComputeArithmetic():
  Series(){
  std::cout <<"Compute Arithmetic object constructed"<<std::endl;}

/*---------------------------------------------------------------*/
double ComputeArithmetic::computeTerm (Uint K) {

  return 1.0 * K ;
}
