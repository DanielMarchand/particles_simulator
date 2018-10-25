#include "series.hh"


class ComputeArithmetic : public Series {
  //Constructor
  ComputeArithmetic() ;
  //Destructor
  ~ComputeArithmetic() = default;

  double compute (Uint N) override ;

  double computeTerm (Uint K) override;
}
