#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<std::complex<int>> computeFrequencies(int size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
  Matrix<complex> m_out (m_in.cols());
  fftw_complex* m_in_double = reinterpret_cast<double(*)[2]> (m_in.data());
  fftw_complex* m_out_double = reinterpret_cast<double(*)[2]> (m_out.data());
  auto fftw_plan = fftw_plan_dft_2d(m_in.rows(),
                                    m_in.cols(),
                                    m_in_double,
                                    m_out_double,
                                    -1,
                                    FFTW_ESTIMATE);
  fftw_execute(fftw_plan);
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
  Matrix<complex> m_out (m_in.cols());
  fftw_complex* m_in_double = reinterpret_cast<double(*)[2]> (m_in.data());
  fftw_complex* m_out_double = reinterpret_cast<double(*)[2]> (m_out.data());
  auto fftw_plan = fftw_plan_dft_2d(m_in.rows(),
                                    m_in.cols(),
                                    m_in_double,
                                    m_out_double,
                                    +1,
                                    FFTW_ESTIMATE);
  fftw_execute(fftw_plan);
  return m_out;
}

/* ------------------------------------------------------ */


/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {

}

#endif  // FFT_HH
