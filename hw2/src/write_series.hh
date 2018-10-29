#include "dumper_series.hh"
#ifndef WRITE_SERIES_H
#define WRITE_SERIES_H

class WriteSeries: public DumperSeries{
public:
  // Constructor
  WriteSeries(std::unique_ptr<Series>& series_inp, Uint maxiter_inp, Uint freq_inp);
  // Destructor
  virtual ~WriteSeries() = default;

  void dump(std::ostream & os = std::cout) override;
  void set_seperator(std::string seperator);

protected:
  int maxiter;
  int freq;
  std::string seperator;
};

#endif /* WRITE_SERIES_H */
