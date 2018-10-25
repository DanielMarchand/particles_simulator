#include "series.hh"


class ComputeArithmetic : public Series {
  //Constructor
  ComputeArithmetic() ;
  //Destructor
  ~ComputeArithmetic() = default;

  double computeTerm (Uint K) override;
}
