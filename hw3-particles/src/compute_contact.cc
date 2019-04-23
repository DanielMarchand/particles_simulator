#include "compute_contact.hh"
#include "ping_pong_ball.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeContact::setPenalty(Real penalty) {
  this->penalty = penalty;
}
/* -------------------------------------------------------------------------- */
void ComputeContact::computePairInteraction(Particle& par1, Particle& par2) {

  // cast as pingpong
  PingPongBall &ping1 = static_cast<PingPongBall &>(par1);
  PingPongBall &ping2 = static_cast<PingPongBall &>(par2);


  // compute the distance vector and the square of distance
  auto v_r = par2.getPosition() - par1.getPosition(); //distance
  auto r2 = v_r.squaredNorm();   // normed square of distance

  // compute the distance
  auto r = sqrt(r2);
  v_r *= 1 / r;

  if ((ping1.getRadius() + ping2.getRadius()) - r < 0.)
    return;

  // compute the pair force
  auto force = v_r * this->penalty *
    (ping1.getRadius() + ping2.getRadius() - r) / r;

  // add up the force for both concerned particles
  par2.getForce() += force;
  par1.getForce() -= force;

  // remove some velocity as friction
  par1.getVelocity() *= 0.99;
  par2.getVelocity() *= 0.99;
}
