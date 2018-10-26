#include <iostream>
#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "dumper_series.hh"
#include "print_series.hh"

int main(int argc, char *argv[])
{
  ComputeArithmetic &my_arithmetic=ComputeArithmetic();
  Uint a = 1000;
  Uint b = 100;
  PrintSeries my_printseries(my_arithmetic, a, b);
  return 0;
}
