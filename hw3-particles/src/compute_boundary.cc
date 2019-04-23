#include "compute_boundary.hh"
/* -------------------------------------------------------------------------- */
ComputeBoundary::ComputeBoundary(const Vector& xmin, const Vector& xmax)
    : xmin(xmin), xmax(xmax) {
}
/* -------------------------------------------------------------------------- */

void ComputeBoundary::compute(System& system) {


  Real friction_penalty = 0.95; //TODO make friction a 'property'
  for (auto& par : system) {
    for(int i=0; i < 3; ++i){
      if( par.getPosition()[i] >=  this->xmax[i]){
        par.getVelocity()[i] = -par.getVelocity()[i] * friction_penalty;
      }
      if( par.getPosition()[i] <=  this->xmin[i]){
        par.getVelocity()[i] = -par.getVelocity()[i] * friction_penalty;
      }
    }
  }

}

/* -------------------------------------------------------------------------- */
