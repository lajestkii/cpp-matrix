#include "../s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!isValidMatrix(other)) throw std::invalid_argument("Invalid Matrix");

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!isValidMatrix(other)) throw std::invalid_argument("Invalid Matrix");

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (other.rows_ != rows_ || other.cols_ != cols_) return false;
  if (other.matrix_ == nullptr && matrix_ == nullptr) return true;
  if (other.matrix_ == nullptr || matrix_ == nullptr) return false;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[i][j] != other.matrix_[i][j]) return false;
    }
  }
  return true;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ != other.cols_) throw std::invalid_argument("Invalid Matrix");

  S21Matrix temp(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = S21Matrix(std::move(temp));
}

S21Matrix S21Matrix::Transpose() {
  if (rows_ == 0 || cols_ == 0 || matrix_ == nullptr)
    throw std::invalid_argument("Invalid Matrix");

  S21Matrix transpose_matrix(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transpose_matrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transpose_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ < 1 || cols_ < 1 || matrix_ == nullptr)
    throw std::invalid_argument("Invalid Matrix");

  if (rows_ != cols_) throw std::invalid_argument("Invalid Matrix");

  S21Matrix calc_complements(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix temp = minor_matrix(i, j);
      calc_complements(i, j) = pow(-1, (i + j)) * temp.Determinant();
    }
  }
  return calc_complements;
}

double S21Matrix::Determinant() {
  if (rows_ < 1 || cols_ < 1 || matrix_ == nullptr)
    throw std::invalid_argument("Invalid Matrix");

  if (rows_ != cols_) throw std::invalid_argument("Invalid Matrix");

  return this->determinant();
}

double S21Matrix::determinant() {
  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double res = 0.0;

  for (int i = 0; i < cols_; ++i) {
    S21Matrix temp = minor_matrix(0, i);
    if (i % 2 == 0) {
      res += matrix_[0][i] * temp.determinant();
    } else {
      res -= matrix_[0][i] * temp.determinant();
    }
  }
  return res;
}

S21Matrix S21Matrix::minor_matrix(int row, int col) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int res_row = 0, res_col = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i == row) continue;
    res_col = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == col) continue;
      minor.matrix_[res_row][res_col] = matrix_[i][j];
      res_col++;
    }
    res_row++;
  }
  return minor;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ < 1 || cols_ < 1 || matrix_ == nullptr)
    throw std::invalid_argument("Invalid Matrix");

  if (rows_ != cols_)
    throw std::invalid_argument("Different size of rows and cols");

  double det = this->Determinant();
  if (det == 0.0) throw std::invalid_argument("Determinant is zero");

  S21Matrix calc_complements = this->CalcComplements();
  S21Matrix inverse_matrix = calc_complements.Transpose();

  inverse_matrix.MulNumber((1 / det));
  return inverse_matrix;
}