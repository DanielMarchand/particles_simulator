#include "dumper_series.hh"
#ifndef WRITE_SERIES_H
#define WRITE_SERIES_H

class WriteSeries: public DumperSeries{
public:
  // Constructor
  WriteSeries(Series &series_inp, Uint maxiter_inp, Uint freq_inp);
  // Destructor
  virtual ~WriteSeries() = default;

  void dump() override;
  void set_seperator(std::string seperator);

protected:
  int maxiter;
  int freq;
  std::string seperator;
  std::string file_ending;
};

#endif /* WRITE_SERIES_H */
