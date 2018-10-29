#include "series.hh"
#include <memory>
#ifndef DUMPER_SERIES_H
#define DUMPER_SERIES_H

class DumperSeries {
public:
  // Constructor:
  DumperSeries(std::unique_ptr<Series>& series_inp);
  // Destructor:
  virtual ~DumperSeries() = default ;


  // overwriting the dump method
  virtual void dump(std::ostream & os = std::cout) = 0;

  void set_seperator(std::string seperator);
  void setPrecision(Uint new_precision);



  // TODO: overload print stream operator here
protected:
  std::unique_ptr<Series>& series;
  //Series &series;
  Uint precision;
  std::string seperator;


};


inline std::ostream & operator << (std::ostream & stream,
                                   DumperSeries & _this){
  _this.dump(stream);
  return stream;
}
#endif /* DUMPER_SERIES_H */
