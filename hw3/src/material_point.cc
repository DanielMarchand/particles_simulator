#include "material_point.hh"

/* -------------------------------------------------------------------------- */
void MaterialPoint::printself(std::ostream& stream) const {
  Particle::printself(stream);
  stream <<
    " " << position_x  << " " << position_y <<
    " " << temperature <<
    " " << heat_rate;
}

/* -------------------------------------------------------------------------- */

void MaterialPoint::initself(std::istream& sstr) {
  Particle::initself(sstr);
  sstr >> position_x >> position_y >> temperature  >> heat_rate;;
}
