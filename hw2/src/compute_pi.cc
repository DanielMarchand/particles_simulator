#include "compute_pi.hh"

double ComputePi::compute (Uint N) override {
  Series::compute(N);
  return math::sqrt(6.*this->current_value);
}





double ComputePi::computeTerm (Uint K) override{

  return 1.0 / (K*K);
}
