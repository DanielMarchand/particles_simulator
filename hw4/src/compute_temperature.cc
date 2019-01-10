#include "compute_temperature.hh"

/* -------------------------------------------------------------------------- */

void ComputeTemperature::setDeltaT(const Real &dt) { this->dt = dt; }

void ComputeTemperature::setConductivityK(const Real &conductivityK) {

  this->conducivityK = conductivityK;
}

void ComputeTemperature::setDensity(const Real &density) {

  this->density = density;
}

void ComputeTemperature::setCapacity(const Real &capacity) {

  this->capacity = capacity;
}

void ComputeTemperature::setBorderTempFlag(bool set_bordertemp_zero){

  this->set_bordertemp_zero = set_bordertemp_zero;

}


Real ComputeTemperature::getDeltaT() { return this->dt; }

Real ComputeTemperature::getConductivityK() {

  return this->conducivityK;
}

Real ComputeTemperature::getDensity() {

  return this->density ;
}

Real ComputeTemperature::getCapacity() {

  return this->capacity ;
}



/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System &system) {
  UInt Nb_particles = system.getNbParticles();
  UInt size = sqrt(Nb_particles);
  std::vector<Real> tempeatures;
  std::vector<Real> heat_rates;

  for (auto &par : system) {
    auto &mat_par = static_cast<MaterialPoint &>(par);
    tempeatures.push_back(mat_par.getTemperature());
    heat_rates.push_back(mat_par.getHeatRate());
  }

  auto temperatures_matrix = this->makeMatrix(tempeatures);
  auto heat_rates_matrix = this->makeMatrix(heat_rates);

  // Fourier Transform of temperature and heat rate :
  auto temperatures_fft = FFT::transform(temperatures_matrix);
  auto heat_rates_fft = FFT::transform(heat_rates_matrix);
  auto squared_freqs = FFT::computeFrequenciesSquaredNorm(size);

  // dθₙ/dt =(1/(ρc)) * (hᵥ - κ * θₙ₊₁ *(qx² +qy²)) [Fourier space] =>
  // θₙ₊₁ = ( (Δt*hᵥ/ρC) + θₙ) / (1 + (Δt*κ/ρC)(qx² +qy²) ) [Fourier space]
  auto scalar_temp = dt / (this->capacity * this->density);
  auto denumenator_fft = Matrix<complex>(size);
  auto numenator_fft = Matrix<complex>(size);

  numenator_fft = matrixmatrixAdd(scalarmatrixMult(scalar_temp, heat_rates_fft),
                                  temperatures_fft);

  denumenator_fft = scalarmatrixAdd(
      1.0, scalarmatrixMult(scalar_temp * this->conducivityK, squared_freqs));

  temperatures_fft = matrixmatrixElementDivide(numenator_fft, denumenator_fft);
  temperatures_matrix = FFT::itransform(temperatures_fft);

  // updating particles' temperature with the updated temperature matrix
  updateParticleTemperatures(system, temperatures_matrix);
}
