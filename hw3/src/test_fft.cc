#include "my_types.hh"
#include "fft.hh"
#include <gtest/gtest.h>

/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry); //NOTE j is unused here..
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform) {
  //TODO pull general elements out into a test setup
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry); //NOTE j is unused here..
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);
  Matrix<complex> inv_res = FFT::itransform(res);

  // Check that the F^-1F(m) == m
  for (auto&& entry : index(m)) {
    for (auto&& inv_entry : index(inv_res)) {
      auto& val = std::get<2>(entry);
      auto& inv_val = std::get<2>(inv_entry);
      std::cout << "val: "  << val << std::endl;
      std::cout << "inv_val: " << inv_val << std::endl;
      //NOTE std::abs does not check the sign adequately
      ASSERT_NEAR(std::abs(val), std::abs(inv_val), 1e-10);
    }
  }
}
/*****************************************************************/
