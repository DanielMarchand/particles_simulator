#include "series.hh"
#include <cmath>

Series::series():
  current_term{0},
  current_value{0.0}
{}
void Series::addTerm(){
  this->current_term++;
  this->current_value += this->computeTerm(this->current_term);
}

double Series::getAnalyticalPrediction(){
  return cmath::NAN;
}
