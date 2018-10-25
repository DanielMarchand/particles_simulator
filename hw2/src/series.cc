#include "series.hh"
#include <cmath>

void Series::addTerm(){
  this->current_term++;
  this->current_value += this->computeTerm(this->current_term);
}

double Series::getAnalyticalPrediction(){
  return cmath::NAN;
}
