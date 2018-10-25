#include "compute_arithmetic.hh"

double ComputeArithmetic::compute (Uint N) override {
  if (this->current_term <= N) {
    N = - this-> current_term;
  }else {
    this->current_value = 0.0;
    this->current_term = 0 ;
  }

  for (int k{0}; k < N ; ++k){
    this->addTerm();
  }
  return this->current_value;
}





double ComputeArithmetic::computeTerm (Uint K) override{

  return 1.0 * K ;
}
