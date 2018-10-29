#include "dumper_series.hh"


DumperSeries::DumperSeries(std::unique_ptr<Series>& series_inp):
  series{series_inp},
  precision{4}
  {};
/*-----------------------------------------------------*/

void DumperSeries::setPrecision(Uint new_precision){
  this->precision = new_precision ;
}
