#include "series.hh"
#ifndef DUMPER_SERIES_H
#define DUMPER_SERIES_H

class DumperSeries {
public:
  // Constructor:
  DumperSeries(Series &series_inp);
  // Destructor:
  virtual ~DumperSeries() = default ;

  virtual void dump() = 0 ;

  void setPrecision(Uint new_precision);

  // TODO: overload print stream operator here
protected:
  Series &series;
  Uint precision;

};

#endif /* DUMPER_SERIES_H */
