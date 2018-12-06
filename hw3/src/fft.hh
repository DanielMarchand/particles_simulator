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
  static Matrix<std::complex<Real>> computeFrequenciesSquaredNorm(int size);
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
  UInt N = size;
  Matrix<std::complex<int>> frequency_matrix(N);

  double max_delta = double(N) / 2;

  for (auto&& entry : index(frequency_matrix)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    int i_val = i;
    if(i >= max_delta){
      i_val = i_val - N;
    }
    int j_val = j;
    if(j >= max_delta){
      j_val = j_val - N;
    }

    val.real(i_val);
    val.imag(j_val);
  }

  return frequency_matrix;

}

/* ------------------------------------------------------ */

inline Matrix<std::complex<Real>> FFT::computeFrequenciesSquaredNorm(int size) {
  UInt N = size;
  Matrix<std::complex<Real>> frequency_matrix(N);

  double max_delta = double(N) / 2;

  for (auto&& entry : index(frequency_matrix)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    int i_val = i;
    if(i >= max_delta){
      i_val = i_val - N;
    }
    int j_val = j;
    if(j >= max_delta){
      j_val = j_val - N;
    }

    val.real(i_val*i_val + j_val * j_val);
    val.imag(0.0);
  }

  return frequency_matrix;

}

#endif  // FFT_HH
