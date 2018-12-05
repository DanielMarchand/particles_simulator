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

    // Check that there are only two frequencies at i,j=0 and i=N-1, j=0
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
  //NOTE can consider pulling general elements out into a test setup
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

  std::cout << m.size() << std::endl;

  // Check that the F^-1F(m) == m * N*N (FFTW does not normalize)
  for (auto&& entry : index(m)) {
      UInt i = std::get<0>(entry);
      UInt j = std::get<1>(entry);
      auto& val = std::get<2>(entry);
      auto& inv_val = inv_res(i,j);

      //NOTE std::abs does not check the sign adequately
      ASSERT_NEAR(std::abs(val), std::abs(inv_val)/(N*N), 1e-10);
    }
}
/*****************************************************************/

TEST(FFT, compute_frequency) {
  UInt N = 512;
  Matrix<std::complex<int>> frequency_matrix = FFT::computeFrequencies(N);

  for (auto&& entry : index(frequency_matrix)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    if (i == 0)
      ASSERT_NEAR(val.real(), 0, 1e-10);
    else if (j == 0)
      ASSERT_NEAR(val.imag(), 0, 1e-10);
    else if (i == N - 1)
      ASSERT_NEAR(val.real(), -1, 1e-10);
    else if (j == N - 1)
      ASSERT_NEAR(val.imag(), -1, 1e-10);
  }
}
