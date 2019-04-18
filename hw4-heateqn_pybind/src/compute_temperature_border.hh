#ifndef __COMPUTE_TEMPERATURE_BORDER__HH__
#define __COMPUTE_TEMPERATURE_BORDER__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "matrix.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

//! Compute contact interaction between ping-pong balls
class ComputeTemperatureBorder : public Compute {

  // Virtual implementation
public:
  void compute(System& system) override;
  inline void updateParticleTemperatures(System& system);

};

/* -------------------------------------------------------------------------- */
inline void ComputeTemperatureBorder::updateParticleTemperatures(System &system){
  UInt Nb_particles = system.getNbParticles();
  UInt size = sqrt(Nb_particles);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      auto& par = system.getParticle(i * size +j);
      auto& mat_par = static_cast<MaterialPoint&>(par);
      auto& temp = mat_par.getTemperature();

      // currently the only boundary condition is setting temp to 0 at borders
      if (i == 0 || j == 0 || i == size -1 || j == size -1){
        temp = 0;
      }
    }
  }

}



/* -------------------------------------------------------------------------- */
#endif //  __COMPUTE_TEMPERATURE_BORDER__HH__
