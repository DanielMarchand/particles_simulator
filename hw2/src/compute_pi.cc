#include "compute_pi.hh"
#include <math.h>

ComputePi::ComputePi():
  Series()
{}
/*---------------------------------------------------------------*/
double ComputePi::compute (int N)  {
  Series::compute(N);
  //std::cout<<"current:"<<this->current_value<<std::endl;
  //std::cout<<"Pi:"<<sqrt(6.*this->current_value)<<std::endl;
  return sqrt(6.*this->current_value);
}

/*---------------------------------------------------------------*/
double ComputePi::computeTerm (Uint K) {
  //std::cout<<"K:"<<K<<std::endl;
  //std::cout<<"1/(K*K):"<<1.0 / (K*K)<<std::endl;
  return 1.0 / (K*K);

}
/*---------------------------------------------------------------*/

double ComputePi::getAnalyticPrediction() {
  return M_PI;
}
