#include "compute_temperature.hh"

/* -------------------------------------------------------------------------- */

void ComputeTemperature::setDeltaT(Real dt) {

  this->dt = dt;

}

void ComputeTemperature::setDeltaConductivityK(Real conductivityK){

  this->conducivityK = conductivityK ;

}

void ComputeTemperature::setDeltaDensity(Real density){

  this->density = density;
}

void ComputeTemperature::setDeltaCapacity(Real capacity){

  this->capacity = capacity;

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
  auto temps_multiplied_sq_freqs = matrixmatrixElementMult(temperatures_fft,
                                                           squared_freqs);
  temps_multiplied_sq_freqs = scalarmatrixMult(this->conducivityK,
                                               temps_multiplied_sq_freqs);
  auto temperature_derivative_fft = Matrix<complex>(size);
  temperature_derivative_fft = matrixmatrixSubtract(heat_rates_fft,
                                                    temps_multiplied_sq_freqs);
  temperature_derivative_fft = scalarmatrixMult((1/this->density / this->capacity),
                                                temperature_derivative_fft);
  // Inverse Fourier Transform of temperature derivative:
  auto temperature_derivative = FFT::itransform(temperature_derivative_fft);

  // θₙ₊₁ = θₙ + Δt * ∂θₙ/∂t [Real space]
  temperatures_matrix = matrixmatrixAdd (temperatures_matrix,
                                         scalarmatrixMult(dt,
                                                          temperature_derivative));
  // updating particles' temperature with the updated temperature matrix
  updateParticleTemperatures(system, temperatures_matrix);
}
