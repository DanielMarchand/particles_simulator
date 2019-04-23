#ifndef __COMPUTE_CONTACT__HH__
#define __COMPUTE_CONTACT__HH__

/* -------------------------------------------------------------------------- */
#include "compute_interaction.hh"

//! Compute contact interaction between ping-pong balls
class ComputeContact : public ComputeInteraction {

  // Virtual implementation
public:
  //! Penalty contact implementation
  void computePairInteraction(Particle& par1, Particle& par2) override;

  // Accessors
public:
  //! Set penalty
  void setPenalty(Real penalty);

  // Members
protected:
  Real penalty{1000};
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_CONTACT__HH__
