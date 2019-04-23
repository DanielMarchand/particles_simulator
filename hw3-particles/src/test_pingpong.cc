#include "compute_boundary.hh"
#include "compute_contact.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "ping_pong_ball.hh"
#include "ping_pong_balls_factory.hh"
#include "system.hh"
#include <gtest/gtest.h>

/*****************************************************************/
// Fixture class
class RandomPingPongs : public ::testing::Test {
protected:
  void SetUp() override {
    //PingpongsFactory::getInstance();
    PingPongBallsFactory::getInstance();
    std::vector<PingPongBall> pingpong_balls;
    n_pingpongs = 10;
    for (UInt i = 0; i < n_pingpongs; ++i) {
      PingPongBall p;
      p.getPosition() = 1.;
      p.getMass() = 1.;
      pingpong_balls.push_back(p);
    }

    for (auto& p : pingpong_balls) {
      // std::cout << p << std::endl;
      system.addParticle(std::make_shared<PingPongBall>(p));
    }
  }

  System system;
  UInt n_pingpongs;
};

/*****************************************************************/
TEST_F(RandomPingPongs, csv) {
  CsvWriter writer("tmp_file");
  writer.compute(system);

  CsvReader reader("tmp_file");
  System s_fromfile;
  reader.compute(s_fromfile);

  UInt read_n_pingpongs = s_fromfile.getNbParticles();
  EXPECT_EQ(n_pingpongs, read_n_pingpongs);

  for (UInt i = 0; i < n_pingpongs; ++i) {
    auto& part1 = system.getParticle(i);
    auto& pos1 = part1.getPosition();
    auto& part2 = s_fromfile.getParticle(i);
    auto& pos2 = part2.getPosition();
    for (UInt j = 0; j < 3; ++j) {
      ASSERT_NEAR(pos1[j], pos2[j], std::abs(pos1[j]) * 1e-12);
    }
  }
}

// Fixture class
class TestBorder : public ::testing::Test {

protected:
  void SetUp() override {
    PingPongBall p;
    p.getMass() = 1.;
    p.getPosition() =  0;
    p.getVelocity() =  0;
    system.addParticle(std::make_shared<PingPongBall>(p));

    auto verlet = std::make_shared<ComputeVerletIntegration>(0.05);
    Vector xmin;
    Vector xmax;
    xmin = 0;
    xmax = 20;

    boundary = std::make_shared<ComputeBoundary>(xmin, xmax);
    contact = std::make_shared<ComputeContact>();
    verlet = std::make_shared<ComputeVerletIntegration>(1.);
    verlet->addInteraction(this->contact);
  }

  System system;

  std::shared_ptr<ComputeContact> contact;
  std::shared_ptr<ComputeBoundary> boundary;
  std::shared_ptr<ComputeVerletIntegration> verlet;
};

TEST_F(TestBorder, reverse_sign) {

  auto& p = system.getParticle(0);
  p.getVelocity()[1] = 1.0;
  p.getPosition()[0] = -0.1;

  this->boundary->compute(system);

  ASSERT_LT(p.getVelocity()[1], 0);
}
