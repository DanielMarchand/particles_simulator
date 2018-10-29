#include "print_series.hh"
#include <string>
#include <iostream>

PrintSeries::PrintSeries(Series &series_inp, Uint maxiter_inp, Uint freq_inp):
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
  for (int i{1}; i < N; ++i) {
    res = this->series.compute(i * this->freq-1);
    res2 = this->series.compute(i * this->freq);

    os << os.precision(this->precision)<<
        i*this->freq <<"    "<< res <<"    "<< res2-res <<std::endl ;

  }


}
