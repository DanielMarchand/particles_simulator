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

  Real timestep = 1;
  compute_temp->compute(system);
  compute_temp->setDeltaT(timestep);

  for (auto& par : system) {
    auto& mat_par = static_cast<MaterialPoint&>(par);
    ASSERT_NEAR(mat_par.getTemperature(), 1.0, 1e-10);
  }

}

// Fixture class
class VolumetricHeatSource : public ::testing::Test {
protected:
  void SetUp() override {
    MaterialPointsFactory::getInstance();
    std::vector<MaterialPoint> material_points;
    Real test_temp = 0;
    Real test_heatrate = 0;
    size =  512;// 512;
    this->number_mat_points = size*size;

    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        MaterialPoint p;
        Real real_size = size;
        Real real_i = i;
        Real real_j = j;
        p.getPositionX() = (real_i - (real_size -1) / 2) / ((real_size -1) / 2);
        p.getPositionY() = (real_j - (real_size -1) / 2) / ((real_size -1) / 2);;
        p.getTemperature() = test_temp;
        p.getHeatRate() = test_heatrate;

        // Apply boundary conditions
        if (i==size/4){
          p.getHeatRate() = -1;
        }
        else if (i== (3*size)/4){
          p.getHeatRate() =  1;
        }
        material_points.push_back(p);

      }
    }

    for (auto& p : material_points) {
      system.addParticle(std::make_shared<MaterialPoint>(p));
    }

    compute_temp = std::make_shared<ComputeTemperature>();
    Real timestep = 1;
    compute_temp->setDeltaT(timestep);
    compute_temp->set_bordertemp_zero = false;



  }

  System system;
  int size;
  UInt number_mat_points;
  std::vector<Real> previous_solution;

  std::vector<Real> new_solution;
  std::shared_ptr<ComputeTemperature> compute_temp;
};
/*****************************************************************/
TEST_F(VolumetricHeatSource, temperature_change) {
  UInt nsteps =  5; // found to be enough timesteps to reach convergence;
  UInt freq   =  1;

  for (UInt i = 0; i < nsteps; ++i) {
    if (i % freq == 0 || i == 0) {
      int iterr = 0 ;
      for (auto& par : system){

        auto& mat_par = static_cast<MaterialPoint&>(par);
        Real pos_x = mat_par.getPositionX();
        if (pos_x == -1) { iterr ++;}
        Real expected_temp;
        if (pos_x < -0.5){
          expected_temp = (-pos_x - 1);
        }
        else if (pos_x >= -0.5 && pos_x <= 0.5){
          expected_temp = pos_x;
        }
        else if (pos_x > 0.5){
          expected_temp = -pos_x + 1;
        }
      }


    }
    compute_temp->compute(system);

    // update the 'old solution' vector
    new_solution.clear();
    for (auto& par : system) {
      auto& mat_par = static_cast<MaterialPoint&>(par);
      if (mat_par.getPositionY() == 0){
        new_solution.push_back(mat_par.getTemperature());
      }
    }
  }

  for (auto& par : system) {
    auto& mat_par = static_cast<MaterialPoint&>(par);
    Real pos_x = mat_par.getPositionX();
    Real expected_temp;
    Real real_size = size;
    Real temp_accuarcy = 0.01;
    if (pos_x < -0.5){
      expected_temp = (-pos_x - 1)/real_size;
      ASSERT_NEAR(mat_par.getTemperature(), expected_temp, temp_accuarcy);
    }
    else if (pos_x >= -0.5 && pos_x <= 0.5){
      expected_temp = pos_x/real_size;
      ASSERT_NEAR(mat_par.getTemperature(), expected_temp, temp_accuarcy);
    }
    else if (pos_x > 0.5){
      expected_temp = (-pos_x + 1)/real_size;
      ASSERT_NEAR(mat_par.getTemperature(), expected_temp, temp_accuarcy);
    }
  }

}
