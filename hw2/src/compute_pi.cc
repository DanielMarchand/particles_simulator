#include "compute_pi.hh"
#include <math.h>

ComputePi::ComputePi():
  Series(){
  std::cout <<"Compute Pi object constructed"<<std::endl;
}
/*---------------------------------------------------------------*/
double ComputePi::compute (int N)  {
  Series::compute(N);
  return sqrt(6.*this->current_value);
}

/*---------------------------------------------------------------*/
double ComputePi::computeTerm (Uint K) {
  return 1.0 / (K*K);

}
/*---------------------------------------------------------------*/

double ComputePi::getAnalyticPrediction() {
  return M_PI;
}
