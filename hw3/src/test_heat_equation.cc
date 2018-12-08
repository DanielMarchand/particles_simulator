#include "compute_temperature.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_point.hh"
#include "material_points_factory.hh"
#include "system.hh"
#include <gtest/gtest.h>

/*****************************************************************/
// Fixture class
class HomogeneousTemp_ZeroFlux : public ::testing::Test {
protected:
  void SetUp() override {
    MaterialPointsFactory::getInstance();
    std::vector<MaterialPoint> material_points;
    Real test_temp = 1;
    Real test_heatrate = 0;
    UInt size = 10;
    this->number_mat_points = size*size;
    for (UInt i = 0; i < size; ++i) {
      for (UInt j = 0; j < size; ++j) {
        MaterialPoint p;
        p.getPositionX() = i;
        p.getPositionY() = j;
        p.getTemperature() = test_temp;
        p.getHeatRate() = test_heatrate;
        material_points.push_back(p);
      }
    }

    for (auto& p : material_points) {
      system.addParticle(std::make_shared<MaterialPoint>(p));
    }

    compute_temp = std::make_shared<ComputeTemperature>();
    compute_temp->set_bordertemp_zero = false;
  }

  System system;
  UInt number_mat_points;

  std::shared_ptr<ComputeTemperature> compute_temp;
};

/*****************************************************************/
TEST_F(HomogeneousTemp_ZeroFlux, csv) {
  CsvWriter writer("tmp_file");
  writer.compute(system);

  CsvReader reader("tmp_file");
  System s_fromfile;
  reader.compute(s_fromfile);

  UInt read_n_planets = s_fromfile.getNbParticles();
  EXPECT_EQ(number_mat_points, read_n_planets);

  //NOTE we can add more sophisticated reader/writer tests
  //for (UInt i = 0; i < number_mat_points; ++i) {
  //  auto& part1 = system.getParticle(i);
  //  auto& pos1 = part1.getPosition();
  //  auto& part2 = s_fromfile.getParticle(i);
  //  auto& pos2 = part2.getPosition();
  //  for (UInt j = 0; j < 3; ++j) {
  //    ASSERT_NEAR(pos1[j], pos2[j], std::abs(pos1[j]) * 1e-12);
  //  }
  //}
}
/*****************************************************************/
TEST_F(HomogeneousTemp_ZeroFlux, temperature_change) {
  compute_temp->compute(system);

  for (auto& par : system) {
    auto& mat_par = static_cast<MaterialPoint&>(par);
    ASSERT_NEAR(mat_par.getTemperature(), 1.0, 1e-10);
  }

}
