#include "series.hh"


class ComputePi : public Series {
  //Constructor
  ComputePi() ;
  //Destructor
  ~ComputePi() = default;

  double compute (Uint N) override ;

  double computeTerm (Uint K) override;

  double getAnalyticalPrediction () override;
}
