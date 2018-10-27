#include <iostream>
#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "dumper_series.hh"
#include "print_series.hh"

int main(int argc, char *argv[])
{
  ComputeArithmetic my_arithmetic = ComputeArithmetic();
  ComputePi my_pi = ComputePi();
  int maxiter_inp = 670000000;
  int freq_inp = 100000;
  PrintSeries my_printseries(my_arithmetic,
                             maxiter_inp,
                             freq_inp);

  PrintSeries my_printseries_pi(my_pi,
                                maxiter_inp,
                                freq_inp);
  my_printseries_pi.dump();
  return 0;
}
