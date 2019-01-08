#ifndef __MATERIAL_POINTS_FACTORY__HH__
#define __MATERIAL_POINTS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "functional"
#include "material_point.hh"
#include "particles_factory_interface.hh"
/* -------------------------------------------------------------------------- */

//! Factory for material points
class MaterialPointsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  MaterialPointsFactory() {
    createComputes = [&](Real timestep) {
      this->createDefaultComputes(timestep);
    };
  };

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  SystemEvolution &createSimulation(const std::string &fname, Real timestep,
                                    bool border_flag = false) override;

  template <typename Func>
  SystemEvolution& createSimulation(const std::string& fname, Real timestep,
                                    Func func) {
    createComputes = [&](Real timestep) { func(*this, timestep); };
    return this->createSimulation(fname, timestep);
  }

  void createDefaultComputes(Real timestep);

  std::function<void(Real)> createComputes;
  std::unique_ptr<Particle> createParticle() override;

  static ParticlesFactoryInterface &getInstance();
};

/* -------------------------------------------------------------------------- */
#endif //__MATERIAL_POINTS_FACTORY__HH__
