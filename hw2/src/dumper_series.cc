#include "dumper_series.hh"

DumperSeries::DumperSeries(Series &series_inp){
  this->series = series_inp;
  this->perecision = 4;
};
/*-----------------------------------------------------*/

DumperSeries::setPrecision(Uint new_precision){
  this->precision = new_precision ;
}
