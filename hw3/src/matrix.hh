#ifndef MATRIX_HH
#define MATRIX_HH
/* ------------------------------------------------------ */
#include "my_types.hh"
#include <algorithm>
#include <array>
#include <tuple>
#include <vector>
/* ------------------------------------------------------ */

template <typename T>
struct MatrixIterator {
  MatrixIterator(UInt index, UInt size, T* ptr)
      : index(index), size(size), ptr(ptr){};

  T& operator*() { return ptr[index]; };

  void operator++() { index++; };

  bool operator!=(MatrixIterator& other) { return this->index != other.index; };

  int index, size;
  T* ptr;
};
/* ------------------------------------------------------ */

template <typename T>
struct Matrix {

  Matrix(){};
  Matrix(UInt size) { resize(size); };

  UInt rows() { return this->size(); };
  UInt cols() { return this->size(); };
  UInt size() { return std::sqrt(storage.size()); };

  void resize(UInt size) { storage.resize(size * size); }
  T& operator()(UInt i, UInt j) { return storage[j * this->size() + i]; }

  Matrix& operator/=(const T& c) {
    std::for_each(storage.begin(), storage.end(), [&c](auto& v) { v /= c; });
    return *this;
  };

  T* data() { return &storage[0]; };


  std::vector<T> storage;

  MatrixIterator<T> begin() {
    return MatrixIterator<T>(0, this->size(), this->data());
  };
  MatrixIterator<T> end() {
    return MatrixIterator<T>(storage.size(), this->size(), this->data());
  };

};

/* ------------------------------------------------------ */

template <typename T>
struct MatrixIndexIterator : public MatrixIterator<T> {
  MatrixIndexIterator(UInt index, UInt size, T* ptr)
      : MatrixIterator<T>(index, size, ptr){};

  std::tuple<UInt, UInt, T&> operator*() {

    int i = this->index % this->size;
    int j = this->index / this->size;
    return std::tuple<UInt, UInt, T&>(i, j, this->ptr[this->index]);
  };
};

/* ------------------------------------------------------ */
template <typename T>
struct IndexedMatrix {

  IndexedMatrix(Matrix<T>& mat) : mat(mat){};

  MatrixIndexIterator<T> begin() {
    return MatrixIndexIterator<T>(0, mat.size(), mat.data());
  };
  MatrixIndexIterator<T> end() {
    return MatrixIndexIterator<T>(mat.storage.size(), mat.size(), mat.data());
  };

private:
  Matrix<T>& mat;
};
/* ------------------------------------------------------ */

template <typename T>
IndexedMatrix<T> index(Matrix<T>& mat) {
  return IndexedMatrix<T>(mat);
}
/* ------------------------------------------------------ */

template <typename T>
struct std::iterator_traits<MatrixIterator<T>> {
  using value_type = T;
};

/* ------------------------------------------------------ */

//NOTE: operator overloading would be ideal for matrix multiplication/scalar
//      addition and multiplication but functions were used instead
//      simplicity of development
template<typename T >
inline Matrix<T> matrixmatrixAdd(Matrix<T> mat_1, Matrix<T> mat_2){
  UInt ret_size = mat_1.size();
  Matrix<T> ret_mat(ret_size);
  for (auto&& entry : index(ret_mat)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = mat_1(i,j) + mat_2(i,j);
  }
  return ret_mat;
}

template<typename T >
inline Matrix<T> matrixmatrixSubtract(Matrix<T> mat_1, Matrix<T> mat_2){
  UInt ret_size = mat_1.size();
  Matrix<T> ret_mat(ret_size);
  for (auto&& entry : index(ret_mat)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = mat_1(i,j) - mat_2(i,j);
  }
  return ret_mat;
}


template<typename T, typename P >
inline Matrix<T> matrixmatrixElementMult(Matrix<T> mat_1, Matrix<P> mat_2){
  UInt ret_size = mat_1.size();
  Matrix<T> ret_mat(ret_size);
  for (auto&& entry : index(ret_mat)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = mat_1(i,j) * mat_2(i,j);
  }
  return ret_mat;
}

template<typename T, typename P >
inline Matrix<T> scalarmatrixMult(P t, Matrix<T> mat){
  UInt ret_size = mat.size();
  Matrix<T> ret_mat(ret_size);
  for (auto&& entry : index(ret_mat)) {
    UInt i = std::get<0>(entry);
    UInt j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = t * mat(i,j);
  }
  return ret_mat;
}

/* ------------------------------------------------------ */
#endif //MATRIX
