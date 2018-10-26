#include "series.hh"


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
