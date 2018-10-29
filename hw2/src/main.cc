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
  /*Usage: main series_type dumper_type maxiter freq filename\n\n'
   * '\series_type: pi/algebraic\n'
   * '\tdumper_type: print/plot\n'
   * '\tmaxiter: number of loop iteration to compute the series\n'
   * '\tfreq: frequency at which dumps/plots are made\n\n')
  */
  std::string series_type = argv[1];
  std::string dumper_type = argv[2];
  int maxiter_inp = std::atoi(argv[3]);
  int freq_inp = std::atoi(argv[4]);
  std::string filename = argv[5];

  std::unique_ptr <Series> my_series;

  if ( series_type == "pi" ){
    my_series = std::make_unique<ComputePi>();
  }else if ( series_type == "algebraic"){
    my_series = std::make_unique<ComputeArithmetic>();
  } else {
    std::cerr << "Invalid series_type selected" << std::endl;
  }

  std::ostream *objOstream = &std::cout;
  std::ofstream objOfstream;
  std::unique_ptr <DumperSeries> my_dumper;
  if ( dumper_type == "print" ){
    my_dumper = std::make_unique<PrintSeries> (my_series,
                                               maxiter_inp,
                                               freq_inp);

  } else if ( dumper_type == "write" ){
    my_dumper = std::make_unique<WriteSeries> (my_series,
                                               maxiter_inp,
                                               freq_inp);
    objOfstream.open(filename);
    objOstream = &objOfstream;
  } else {
   std::cerr << "Invalid dumper_type selected" << std::endl;
  }
  my_dumper->setPrecision(8);
  my_dumper->dump(*objOstream);
  objOfstream.close();
  return 0;
}
