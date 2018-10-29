#include <iostream>
#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "dumper_series.hh"
#include "print_series.hh"
#include "write_series.hh"
#include <string>
#include <fstream>
#include <sstream>


std::ofstream ofstream_from_name(std::string filename){
  std::ofstream myfile;
  myfile.open(filename.c_str());
  return myfile;
}


int main(int argc, char *argv[])
{
  ComputeArithmetic my_arithmetic;
  ComputePi my_pi;
  int maxiter_inp = 1000000;
  int freq_inp = 100000;



  PrintSeries my_printseries(my_arithmetic,
                             maxiter_inp,
                             freq_inp);

  PrintSeries my_printseries_pi(my_pi,
                                maxiter_inp,
                                freq_inp);


  my_printseries_pi.setPrecision(7);
  my_printseries_pi.dump();

  my_printseries.setPrecision(6);
  my_printseries.dump();


  WriteSeries my_writeseries_pi(my_pi,
                                maxiter_inp,
                                freq_inp);


  WriteSeries my_writeseries_arithmetic(my_arithmetic,
                                        maxiter_inp,
                                        freq_inp);

  std::string filename = "myfile_pi.txt";
  std::ofstream ofs;  ofs =  ofstream_from_name(filename);
  my_writeseries_pi.dump(ofs);
  ofs.close();

  std::string filename2 = "myfile_arithmetic.txt";
  std::ofstream ofs2;  ofs2 =  ofstream_from_name(filename2);
  my_writeseries_arithmetic.dump(ofs2);
  ofs2.close();
  return 0;
}
