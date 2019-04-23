#include "compute_interaction.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeInteraction::compute(System& system) {
  UInt size = system.getNbParticles();
  // first of all reset forces to zero
  for (auto & particle : system)
    particle.getForce() = 0;

  for (UInt p1 = 0; p1 < size; ++p1) {
    Particle& par1 = system.getParticle(p1);
    for (UInt p2 = p1 + 1; p2 < size; ++p2) {
      Particle& par2 = system.getParticle(p2);
      computePairInteraction(par1, par2);
    }
  }

  // Quick testing of gravity TODO move into 'proper' method
  for (auto & particle : system){
    particle.getForce()[1] -= 100;
  }
}
