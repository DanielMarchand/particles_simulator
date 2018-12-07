#include "material_point.hh"

/* -------------------------------------------------------------------------- */
void MaterialPoint::printself(std::ostream& stream) const {
  stream <<
    " " << position_x  << " " << position_y <<
    " " << temperature <<
    " " << heat_rate;
}

/* -------------------------------------------------------------------------- */

void MaterialPoint::initself(std::istream& sstr) {
  sstr >> position_x >> position_y >> temperature  >> heat_rate;;
}
