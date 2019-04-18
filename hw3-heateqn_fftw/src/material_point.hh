#ifndef __MATERIAL_POINT__HH__
#define __MATERIAL_POINT__HH__

/* -------------------------------------------------------------------------- */
#include "particle.hh"

//! Class for MaterialPoint
class MaterialPoint : public Particle {
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:

  void printself(std::ostream& stream) const override;
  void initself(std::istream& sstr) override;

  Real & getTemperature(){return temperature;};
  Real & getHeatRate(){return heat_rate;};
  Real & getPositionX(){return position_x;};
  Real & getPositionY(){return position_y;};


private:
  // vector was considered for position, but we only need two dimensions
  Real position_x, position_y;

  Real temperature;
  Real heat_rate;

};

/* -------------------------------------------------------------------------- */
#endif  //__MATERIAL_POINT__HH__
