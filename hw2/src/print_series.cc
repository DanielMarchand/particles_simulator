#include "print_series.hh"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

PrintSeries::PrintSeries(std::unique_ptr<Series>& series_inp, Uint maxiter_inp, Uint freq_inp):
  DumperSeries(series_inp)
{
  this->maxiter = maxiter_inp;
  this->freq = freq_inp;
  std::cout <<"Print Series object constructed"<<std::endl;
}


/*-----------------------------------------------------*/

void PrintSeries::dump(std::ostream & os){
  int N = (int) (this->maxiter / this->freq);
  double res = 0;
  double res2 = 0;
  os << this->series->getFirstLine()<<std::endl;

  for (int i{1}; i < N; ++i) {
    res = this->series->compute(i * this->freq-1);
    res2 = this->series->compute(i * this->freq);
    os.setf(std::ios::scientific);
    os.precision(this->precision);

    os << i * this->freq <<"    "<< res <<"    "<< res2-res;
    if ( ! std::isnan(this->series->getAnalyticPrediction()) ) {
      os <<"   " <<this->series->getAnalyticPrediction();
    }
    os << std::endl;
  }
  os << std::endl<<std::endl;


}
