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
  std::string series_type = argv[1];
  std::string dumper_type = argv[2];
  int maxiter_inp = std::stoi(argv[3]);
  int freq_inp = std::stoi(argv[4]);

  std::cout << "TODO: Use shared_unique ptr" << std::endl;
  if ( series_type == "pi" ){
      ComputePi my_series;
  }else if ( series_type == "algebraic"){
      ComputeArithmetic my_series;
  } else {
    std::cerr << "Invalid series_type selected" << std::endl;
  }

  std::cout << "TODO: Use shared_unique ptr" << std::endl;
  if ( dumper_type == "print" ){
    PrintSeries my_dumper(my_series,
                          maxiter_inp,
                          freq_inp);
    std::ostream ofs;  ofs =  std::cout;
  } else if ( dumper_type == "write" ){
    WriteSeries my_dumper(my_series,
                          maxiter_inp,
                          freq_inp);
    std::cout << "TODO: fix how write handles output" << std::endl;
    std::string filename = "myfile.txt";
    std::ofstream ofs;  ofs =  ofstream_from_name(filename);
  } else {
    std::cerr << "Invalid dumper_type selected" << std::endl;
  }

  std::cout << "TODO: setPrecision" << std::endl;
  //my_dumper.setPrecision(7);
  //my_dumper.dump()

  my_dumper.dump(ofs);
  ofs.close();

  return 0;
}
