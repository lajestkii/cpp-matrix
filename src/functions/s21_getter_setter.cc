#include "../s21_matrix_oop.h"

// getters
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

// setter
void S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw std::invalid_argument("invalid argument");
  if (rows == rows_) return;

  double **temp = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    temp[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp[i][j] = matrix_[i][j];
    }
    delete[] matrix_[i];
  }
  for (int i = rows_; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp[i][j] = 0;
    }
  }

  rows_ = rows;
  delete[] matrix_;
  matrix_ = temp;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw std::invalid_argument("invalid argument");
  if (cols == cols_) return;

  double **temp = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    temp[i] = new double[cols];
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp[i][j] = matrix_[i][j];
    }
    delete[] matrix_[i];
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = cols_; j < cols; ++j) {
      temp[i][j] = 0;
    }
  }

  cols_ = cols;
  delete[] matrix_;
  matrix_ = temp;
}
