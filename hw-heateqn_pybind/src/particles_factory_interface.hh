#ifndef __PARTICLES_FACTORY_INTERFACE__HH__
#define __PARTICLES_FACTORY_INTERFACE__HH__

/* -------------------------------------------------------------------------- */
#include "system_evolution.hh"
/* -------------------------------------------------------------------------- */

//! Abstract factory defining interface
class ParticlesFactoryInterface {
  // Constructors/Destructors
protected:
  //! Instance constructor (protected)
  ParticlesFactoryInterface() = default;

public:
  virtual ~ParticlesFactoryInterface() = default;

  // Methods
public:
  //! Create a whole simulation from file
  virtual SystemEvolution &createSimulation(const std::string &fname,
                                            Real timestep,
                                            bool border_flag = false) = 0;
  //! Create a new particle
  virtual std::unique_ptr<Particle> createParticle() = 0;

  //! Get singleton instance
  static ParticlesFactoryInterface &getInstance();

  //! get reference to the system evolution
  SystemEvolution& getSystemEvolution() { return *system_evolution; };

  void setSystemEvolution(std::shared_ptr<SystemEvolution> &system_evolution) {
    this->system_evolution = system_evolution;
  }

  // Members
protected:
  std::vector<Particle *> list_particles;
  std::shared_ptr<SystemEvolution> system_evolution = nullptr;

  // Standard pointer because constructor is protected (cannot use make_unique)
  static ParticlesFactoryInterface *factory;
};

/* -------------------------------------------------------------------------- */
#endif //__PARTICLES_FACTORY_INTERFACE__HH__
