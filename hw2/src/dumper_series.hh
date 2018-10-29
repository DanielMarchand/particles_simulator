#include "series.hh"
#ifndef DUMPER_SERIES_H
#define DUMPER_SERIES_H

class DumperSeries {
public:
  // Constructor:
  DumperSeries(Series &series_inp);
  // Destructor:
  virtual ~DumperSeries() = default ;


  // overwriting the dump method
  virtual void dump(std::ostream & os) = 0;


  void setPrecision(Uint new_precision);



  // TODO: overload print stream operator here
protected:
  Series &series;
  Uint precision;


};


inline std::ostream & operator << (std::ostream & stream,
                                   DumperSeries & _this){
  _this.dump(stream);
  return stream;
}
#endif /* DUMPER_SERIES_H */
