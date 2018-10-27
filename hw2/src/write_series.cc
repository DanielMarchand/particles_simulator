#include "write_series.hh"
#include <string>
#include <iostream>
#include <fstream>


WriteSeries::WriteSeries(Series &series_inp, Uint maxiter_inp, Uint freq_inp):
  DumperSeries(series_inp)
{
  this->maxiter = maxiter_inp;
  this->freq = freq_inp;
  std::cout <<"Write Series object constructed"<<std::endl;
}

/*-----------------------------------------------------*/

void WriteSeries::dump() {
  std::string out = "";
  int N = (int) (this->maxiter / this->freq);
  double res = 0;
  double res2 = 0;
  std::ofstream out_file("toto.txt");
  std::cout<<"TODO: add in precision"<<std::endl;
  for (int i{1}; i < N; ++i) {
    res = this->series.compute(i * this->freq-1);
    res2 = this->series.compute(i * this->freq);
    out_file << i*this->freq <<"    "<< res <<"    "<< res2-res <<std::endl;
  }
  out_file.close();


}
