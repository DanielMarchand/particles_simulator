#include <iostream>
#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "dumper_series.hh"
#include "print_series.hh"
#include "write_series.hh"

int main(int argc, char *argv[])
{
  ComputeArithmetic my_arithmetic = ComputeArithmetic();
  ComputePi my_pi = ComputePi();
  int maxiter_inp = 670000000;
  int freq_inp = 100000;
  WriteSeries my_writeseries_pi(my_pi,
                                maxiter_inp,
                                freq_inp);
  my_writeseries_pi.dump();
  return 0;
}
