#include "series.hh"
#include <cmath>

Series::Series():
  current_term{0},
  current_value{0.0}
{}
/*---------------------------------------------------------------*/
void Series::addTerm(){
  this->current_term++;
  this->current_value += this->computeTerm(this->current_term);
}


/*---------------------------------------------------------------*/
double Series::getAnalyticPrediction(){
  return std::nan("");
}

/*---------------------------------------------------------------*/
double Series::compute (int N) {
  if (this->current_term <= N) {

    N = N - this-> current_term;
  }else {
    this->current_value = 0.0;
    this->current_term = 0 ;

  }
  for (int k{0}; k < N ; ++k){
    this->addTerm();
  }
  return this->current_value;
}
