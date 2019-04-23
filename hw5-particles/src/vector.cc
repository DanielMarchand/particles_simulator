#include "vector.hh"

Real& Vector::operator[](UInt i) {

  return values[i];

}
const Real& Vector::operator[](UInt i) const {

  return values[i];

}

Real Vector::squaredNorm() const {

  Real res = 0;
  for (auto& val : values) {
    res += val * val;
  }
  return res;

}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator+=(const Vector& vec) {

  for (UInt i = 0; i < dim; ++i)
    values[i] += vec[i];

  return *this;
}

Vector& Vector::operator-=(const Vector& vec) {

  for (UInt i = 0; i < dim; ++i)
    values[i] -= vec[i];

  return *this;
}

Vector& Vector::operator*=(Real val) {

  for (auto& v : values)
    v *= val;

  return *this;
}

Vector& Vector::operator/=(Real val) {

  for (auto& v : values)
    v /= val;

  return *this;
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator=(const Vector& vec) {

  std::copy(vec.values.begin(), vec.values.end(), values.begin());

  return *this;
}

Vector& Vector::operator=(Real val) {

  std::fill(values.begin(), values.end(), val);

  return *this;
}

/* -------------------------------------------------------------------------- */

Vector operator+(const Vector& a, const Vector& b) {

  Vector res(a);
  res += b;
  return res;

}

Vector operator-(const Vector& a, const Vector& b) {

  Vector res(a);
  res -= b;
  return res;

}

Vector operator*(const Vector& a, Real val) {

  Vector res(a);
  res *= val;
  return res;

}

Vector operator*(Real val, const Vector& a) {
  return a * val;
}

Vector operator/(const Vector& a, Real val) {

  Vector res(a);
  res /= val;
  return res;

}

/* -------------------------------------------------------------------------- */

/// standard output stream operator
std::ostream& operator<<(std::ostream& stream, const Vector& _this) {

  for (auto& v : _this.values)
    stream << v << " ";

  return stream;
}

/* -------------------------------------------------------------------------- */
/// standard input stream operator
std::istream& operator>>(std::istream& stream, Vector& _this) {

  for (auto& v : _this.values)
    stream >> v;

  return stream;
}
