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
  void setDeltaConductivityK(Real ConductivityK);
  void setDeltaDensity(Real density);
  void setDeltaCapacity(Real capacity);
  inline void updateParticleTemperatures(System& system, Matrix<complex> temperature_matrix);
  inline Matrix<complex> makeMatrix(const std::vector<Real>& vec);

private:
  Real dt {1.0};
  Real conducivityK {1.0};
  Real density {1.0};
  Real capacity {1.0};
};

/* -------------------------------------------------------------------------- */
inline void ComputeTemperature::updateParticleTemperatures
(System& system,Matrix<complex> temperatures_matrix){
  UInt Nb_particles = system.getNbParticles();
  UInt size = sqrt(Nb_particles);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      auto& par = system.getParticle(i * size +j);
      auto& mat_par = static_cast<MaterialPoint&>(par);
      auto& temp = mat_par.getTemperature();
      temp = temperatures_matrix(i,j).real();
    }
  }

}
/*------------------------------------------------------------------------- */


inline Matrix<complex> ComputeTemperature::makeMatrix
(const std::vector<Real>& vec){
  UInt size = sqrt(vec.size());
  UInt iter = 0 ;
  Matrix<complex> ret_mat(size);
  // reshape the contiguous 1D vec into 2D matrix
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      ret_mat(i,j).real(vec[iter]);
      ret_mat(i,j).imag(0.0);
      ++iter;
    }
  }
  return ret_mat;
}




/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
