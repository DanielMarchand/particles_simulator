#ifndef __COMPUTE_INTERACTION__HH__
#define __COMPUTE_INTERACTION__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Base class for interaction computation
class ComputeInteraction : public Compute {
public:
  void compute(System& system) override;

  //! Compute interaction for a pair of particles
  virtual void computePairInteraction(Particle& par1, Particle& par2) = 0;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_INTERACTION__HH__
