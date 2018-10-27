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

void PrintSeries::dump() {
  std::string out = "";
  int N = (int) (this->maxiter / this->freq);
  double res = 0;
  double res2 = 0;
  for (int i{1}; i < N; ++i) {
    std::cout<<i*(this->freq)-1<<std::endl;
    res = this->series.compute(i * this->freq-1);
    res2 = this->series.compute(i * this->freq);

    //my_f
    std::cout << i*this->freq <<"    "<< res <<"    "<< res2-res <<std::endl ;

  }


}
