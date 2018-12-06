#include "compute_temperature.hh"

/* -------------------------------------------------------------------------- */

void ComputeTemperature::setDeltaT(Real dt) {

  this->dt = dt;

}
/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {
  UInt Nb_particles = system.getNbParticles();
  UInt size = sqrt(Nb_particles);
  std::vector<Real> tempeatures;
  std::vector<Real> heat_rates;

  for (auto& par : system) {
    auto& mat_par = static_cast<MaterialPoint&>(par);
    tempeatures.push_back(mat_par.getTemperature());
    heat_rates.push_back(mat_par.getHeatRate());
  }

  auto temperatures_matrix = this->makeMatrix(tempeatures);
  auto heat_rates_matrix   = this->makeMatrix(heat_rates);
  //Fourier Transform of temperature and heat rate :
  auto temperatures_fft = FFT::transform(temperatures_matrix);
  auto heat_rates_fft   = FFT::transform(heat_rates_matrix);
  auto squared_freqs = FFT::computeFrequenciesSquaredNorm(size);

  // dθₙ/dt = hᵥ - κ * θₙ *(qx² +qy²) [Fourier space]
  auto temps_multiplied_sq_freqs = matrixmatrixElementMult(temperatures_fft, squared_freqs);
  auto temperature_derivative_fft = Matrix<complex>(size);
  temperature_derivative_fft = matrixmatrixSubtract(heat_rates_fft,
                                                    temps_multiplied_sq_freqs);
  // Inverse Fourier Transform of temperature derivative:
  auto temperature_derivative = FFT::itransform(temperature_derivative_fft);

  // θₙ₊₁ = θₙ + Δt * ∂θₙ/∂t [Real space]
  temperatures_matrix = matrixmatrixAdd (temperatures_matrix,
                                         scalarmatrixMult(dt,
                                                          temperature_derivative));
  // updating particles' temperature with the updated temperature matrix
  updateParticleTemperatures(system, temperatures_matrix);
}

/* -------------------------------------------------------------------------- */
void ComputeTemperature::updateParticleTemperatures
(System& system,Matrix<complex> temperatures_matrix){
  UInt Nb_particles = system.getNbParticles();
  UInt size = sqrt(Nb_particles);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      auto& par = system.getParticle(i * size +j);
      auto& mat_par = static_cast<MaterialPoint&>(par);
      auto& temp = mat_par.getTemperature();
      temp = temperatures_matrix(i,j).real();
    }
  }

}
/*------------------------------------------------------------------------- */


Matrix<complex> ComputeTemperature::makeMatrix
(std::vector<double> vec){
  int size = sqrt(vec.size());
  int iter = 0 ;
  Matrix<complex> ret_mat ;
  // reshape the contiguous 1D vec into 2D matrix
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      ret_mat(i,j).real(vec.at(iter));
      ret_mat(i,j).imag(0.0);
      ++iter;
    }
  }
  return ret_mat;
}
