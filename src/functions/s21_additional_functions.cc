#include "../s21_matrix_oop.h"

void S21Matrix::s21_allocate_matrix() {
  int i = 0;
  try {
    matrix_ = new double*[rows_];
    for (; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = 0;
      }
    }
  } catch (...) {
    for (int j = 0; j < i; ++j) {
      delete[] matrix_[j];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    throw "Allocation error";
  }
}

void S21Matrix::s21_free_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
        matrix_[i] = nullptr;
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::isValidMatrix(const S21Matrix& other) {
  return other.rows_ == this->rows_ && other.cols_ == this->cols_ &&
         other.matrix_ != nullptr && matrix_ != nullptr;
}

void S21Matrix::MatrixFill(const double* temp) {
  int k = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = temp[k];
      k++;
    }
  }
}