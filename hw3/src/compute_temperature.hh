#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "matrix.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {

  // Virtual implementation
public:
  void compute(System& system) override;
  void setDeltaT(Real dt);
  void updateParticleTemperatures(System& system, Matrix<complex> temperature_matrix);
  Matrix<complex> makeMatrix(std::vector<double> vec);

private:
  Real dt {1.0};
  Real conducivityK {1.0};
  Real density {1.0};
  Real capacity {1.0};
};




/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
