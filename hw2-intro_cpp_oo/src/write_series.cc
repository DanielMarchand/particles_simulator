#include "write_series.hh"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

WriteSeries::WriteSeries(std::unique_ptr<Series>& series_inp, Uint maxiter_inp, Uint freq_inp):
  DumperSeries(series_inp)
{
  this->maxiter = maxiter_inp;
  this->freq = freq_inp;
  this->setSeperator(" ");
}


void WriteSeries::dump(std::ostream & os) {
  std::string out = "";
  int N = (int) (this->maxiter / this->freq);
  double res = 0;
  double res2 = 0;

  //std::ofstream out_file(filename);
  for (int i{1}; i < N; ++i) {
    res = this->series->compute(i * this->freq-1);
    res2 = this->series->compute(i * this->freq);

    os
      << std::scientific << std::setprecision(this->precision);
    os << i * this->freq <<this->seperator<< res <<this->seperator<< res2-res;
    if ( ! std::isnan(this->series->getAnalyticPrediction()) ) {
      os <<this->seperator <<this->series->getAnalyticPrediction();
    }
    os << std::endl;

  }


}
