#include "dumper_series.hh"
#ifndef PRINT_SERIES_H
#define PRINT_SERIES_H

class PrintSeries: public DumperSeries{
public:
  // Constructor
  PrintSeries(Series &series_inp, Uint maxiter_inp, Uint freq_inp);
  // Destructor
  virtual ~PrintSeries() = default;

  void dump() override;

protected:
  int maxiter;
  int freq;
};

#endif /* PRINT_SERIES_H */
