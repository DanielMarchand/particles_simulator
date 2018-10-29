#include <iostream>
#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "dumper_series.hh"
#include "print_series.hh"
#include <iostream>     // std::cout, std::ostream, std::ios
#include <fstream>      // std::filebuf

int main(int argc, char *argv[])
{
  ComputeArithmetic my_arithmetic = ComputeArithmetic();
  ComputePi my_pi = ComputePi();
  int maxiter_inp = 1000000;
  int freq_inp = 100000;

  std::filebuf fb;
  fb.open ("test.txt",std::ios::out);
  std::ostream os(&fb);

  PrintSeries my_printseries(my_arithmetic,
                             maxiter_inp,
                             freq_inp);

  PrintSeries my_printseries_pi(my_pi,
                                maxiter_inp,
                                freq_inp);


  my_printseries_pi.setPrecision(7);
  my_printseries_pi.dump(os);

  my_printseries.setPrecision(6);
  my_printseries.dump();
  return 0;
}
