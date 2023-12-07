#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>
#include <stdexcept>
#include <cmath>


class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;
    
    public:
        S21Matrix();
        explicit S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix();

        int GetRows() const;
        int GetCols() const;
        
        void SetRows(int rows);
        void SetCols(int cols);

        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        bool EqMatrix(const S21Matrix& other) const;
        void MulMatrix(const S21Matrix& other);

        S21Matrix Transpose();
        S21Matrix CalcComplements();
        S21Matrix InverseMatrix();
        double Determinant();

        S21Matrix operator+(const S21Matrix& other) const;
        S21Matrix operator-(const S21Matrix& other) const;
        S21Matrix operator*(const S21Matrix& other) const;
        S21Matrix operator*(const double other) const;

        S21Matrix& operator +=(const S21Matrix& other);
        S21Matrix& operator -=(const S21Matrix& other);
        S21Matrix& operator *=(const S21Matrix& other);
        S21Matrix& operator *=(const double value);

        S21Matrix& operator=(const S21Matrix& other);
        void MatrixFill(const double* temp);
        
        bool operator==(const S21Matrix& other) const;
        double& operator()(const int i, const int j) const;

        friend std::ostream& operator<<(std::ostream& stream, const S21Matrix& matrix) {
            for(int i = 0; i < matrix.rows_; ++i) {
                for(int j = 0; j < matrix.cols_; ++j) {
                    stream << matrix.matrix_[i][j] << " ";
                }
                stream << "\n";
            }
            return stream;
        }
    private:
        void s21_allocate_matrix();
        void s21_free_matrix();
        bool isValidMatrix(const S21Matrix& other);
        double determinant();
        
        S21Matrix minor_matrix(int row, int col);
};



#endif