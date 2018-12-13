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
    //UInt size = 512;
    size =  8;// 512;
    this->number_mat_points = size*size;

    std::cout << size/4 << std::endl;
    std::cout << 3*size/4 << std::endl;
    for (UInt i = 0; i < size; ++i) {
      for (UInt j = 0; j < size; ++j) {
        MaterialPoint p;
        p.getPositionX() = i;
        p.getPositionY() = j;
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

        // record the temp across a horizontal
        if(j==0){
          previous_solution.push_back(test_temp);
          new_solution.push_back(test_temp);
        }
      }
    }

    for (auto& p : material_points) {
      system.addParticle(std::make_shared<MaterialPoint>(p));
    }

    compute_temp = std::make_shared<ComputeTemperature>();
    Real timestep = 1.0;
    compute_temp->setDeltaT(timestep);
    compute_temp->set_bordertemp_zero = false;

    // setup
    del_solution = 100;


  }

  System system;
  UInt size;
  UInt number_mat_points;
  Real del_solution;
  std::vector<Real> previous_solution;
  std::vector<Real> new_solution;

  std::shared_ptr<ComputeTemperature> compute_temp;
};
/*****************************************************************/
TEST_F(VolumetricHeatSource, temperature_change) {
  UInt nsteps = 30;
  UInt freq   =  1;

  for (UInt i = 0; i < nsteps; ++i) {
    if (i % freq == 0 || i == 0) {
      //std::stringstream sstr;
      //sstr << "testdumps/step-" << std::setfill('0') << std::setw(5) << i << ".csv";
      //CsvWriter writer(sstr.str());
      //writer.compute(system);

      std::cout << "iteration i: " <<  i  << "/" << nsteps << std::endl;
      std::cout << "new_sol: ";
      for (auto v_i = new_solution.begin(); v_i != new_solution.end(); ++v_i){
        std::cout << *v_i << ' ';
      }
      std::cout << std::endl;


    }
    compute_temp->compute(system);

    // update the 'old solution' vector
    for (auto& par : system) {
      auto& mat_par = static_cast<MaterialPoint&>(par);
      if (mat_par.getPositionY() == 0){
        new_solution[mat_par.getPositionX()] = mat_par.getTemperature();
      }
    }
  }

  for (auto& par : system) {
    auto& mat_par = static_cast<MaterialPoint&>(par);
    Real pos_x = mat_par.getPositionX();
    Real expected_temp;
    if (pos_x < size/4){
      std::cout << "pos_x size (-pos_x - 1)/size: " <<
        pos_x << " " <<
        size <<  " " <<
        (-pos_x - 1)/size << std::endl;
      expected_temp = (-pos_x - 1)/size;
      ASSERT_NEAR(mat_par.getTemperature(), expected_temp, 1e-5*size);
    }
    else if (pos_x > size/4 && pos_x < (3*size)/4){
      std::cout << "pos_x size (-pos_x - 1)/size: " <<
        pos_x << " " <<
        size <<  " " <<
        (pos_x - 1)/size << std::endl;
      expected_temp = (pos_x - 1)/size;
      ASSERT_NEAR(mat_par.getTemperature(), expected_temp, 1e-5*size);
    }
    else if (pos_x > (3*size)/4){
      std::cout << "pos_x size (-pos_x - 1)/size: " <<
        pos_x << " " <<
        size <<  " " <<
        (-pos_x + 1)/size << std::endl;
      expected_temp = (-pos_x + 1)/size;
      ASSERT_NEAR(mat_par.getTemperature(), expected_temp, 1e-5*size);
    }
  }

  //  ASSERT_NEAR(mat_par.getTemperature(), 1.0, 1e-10);
  //}

}
