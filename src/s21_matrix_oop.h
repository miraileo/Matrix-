#include <cmath>
#include <iostream>

#define EXP 10e7

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double** matrix_;
  void CreateMatrix(int rows, int columns);
  void RemoveMatrix();
  void InitMatrix();
  void CopyMatrix(const S21Matrix& other);

 public:
  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  void GetMinor(int row, int col, const S21Matrix& tmp);
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix Transpose();
  S21Matrix InverseMatrix();

  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);

  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);

  double& operator()(int i, int j);
  double& operator()(int i, int j) const;

  int getRows() { return rows_; }
  int getCols() { return cols_; }
  double** getMatrix() { return matrix_; }
  void SetRows(int rows);
  void SetCols(int cols);
};
