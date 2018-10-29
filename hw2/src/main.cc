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
#include <memory>

std::ofstream ofstream_from_name(std::string filename){
  std::ofstream myfile;
  myfile.open(filename.c_str());
  return myfile;
}


int main(int argc, char *argv[])
{
  std::string series_type = argv[1];
  std::string dumper_type = argv[2];
  int maxiter_inp = std::atoi(argv[3]);
  int freq_inp = std::atoi(argv[4]);
  std::string filename = argv[5];

  std::cout << "TODO: Use shared_unique ptr" << std::endl;
  std::unique_ptr <Series> my_series;

  if ( series_type == "pi" ){
    my_series = std::make_unique<ComputePi>();
  }else if ( series_type == "algebraic"){
    my_series = std::make_unique<ComputeArithmetic>();
  } else {
    std::cerr << "Invalid series_type selected" << std::endl;
  }

  std::unique_ptr <DumperSeries> my_dumper;
  if ( dumper_type == "print" ){
    my_dumper = std::make_unique<PrintSeries> (my_series,
                                               maxiter_inp,
                                               freq_inp);
  } else if ( dumper_type == "write" ){
    my_dumper = std::make_unique<WriteSeries> (my_series,
                                               maxiter_inp,
                                               freq_inp);
    std::ofstream my_file(filename, std::ofstream::out);
    my_dumper->dump(my_file);
    my_file.close();
  } else {
   std::cerr << "Invalid dumper_type selected" << std::endl;
  }


  return 0;
}
