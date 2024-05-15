#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(){this->InitMatrix();}

S21Matrix::S21Matrix(int rows, int cols){
    this->CreateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other) { this->CopyMatrix(other); }

S21Matrix::S21Matrix(S21Matrix&& other) {
  this->CopyMatrix(other);
  other.RemoveMatrix();
}

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    this->RemoveMatrix();
  }
}

void S21Matrix::InitMatrix(){
    this->matrix_ = nullptr;
    this->rows_ = 0;
    this->cols_ = 0;
}

void S21Matrix::CreateMatrix(int rows, int cols){
    if(rows<1||cols<1){
        throw std::length_error("Incorrect matrix");
    }
    this->rows_ = rows;
    this->cols_ = cols;

    this->matrix_ = new double*[rows_]();
    if (this->matrix_ == nullptr) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_]();
    if (this->matrix_[i] == nullptr) {
      for (int j = 0; j < i; j++) {
        delete[] this->matrix_[j];
      }
      delete[] this->matrix_;
      this->InitMatrix();
      throw std::bad_alloc();
    }
  }
}

void S21Matrix::RemoveMatrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->InitMatrix();
  }
}

void S21Matrix::SetCols(int cols){
    if(cols<1){
        throw std::length_error("Amount of cols is less then 1");
    }
    int tmp = 0;
    S21Matrix tmpMatrix(this->rows_, cols);
    if (this->cols_ < cols) {
    tmp = this->cols_;
    } else {
    tmp = cols;
    }
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < tmp; j++) {
      tmpMatrix.matrix_[i][j] = this->matrix_[i][j];
        }
    }
    *this = tmpMatrix;
}

void S21Matrix::SetRows(int rows){
    if(rows<1){
        throw std::length_error("Amount of rows is less then 1");
    }
    int tmp = 0;
    S21Matrix tmpMatrix(rows, this->cols_);
    if (this->rows_ < rows) {
    tmp = this->rows_;
    } else {
    tmp = rows;
    }
    for (int i = 0; i < tmp; i++) {
      for (int j = 0; j < this->cols_; j++) {
      tmpMatrix.matrix_[i][j] = this->matrix_[i][j];
        }
    }
    *this = tmpMatrix;
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  this->CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->RemoveMatrix();
  this->CopyMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  bool tmp = this->EqMatrix(other);
  return tmp;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (other.matrix_ == nullptr || this->matrix_ == nullptr) {
    result = false;
  }
  if(this->rows_ != other.rows_ || this->cols_ != other.cols_) result = false;
  if(result==false) throw std::length_error("Incorrect Matrix");
  for (int i = 0; i < this->rows_ && result; i++) {
    for (int j = 0; j < this->cols_ && result; j++) {
      if (round(this->matrix_[i][j] * EXP)-round(other.matrix_[i][j] * EXP) != 0) {
        result = false;
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other){
  if(this->matrix_==nullptr || other.matrix_ == nullptr || (this->rows_<1 || other.rows_<1)){
    throw std::length_error("The matrix is incorrect");
  }
  else{
    if(this->rows_ == other.rows_){
      for (int i = 0; i < this->rows_; i++){
        for (int j = 0; j < this->cols_; j++){
          this->matrix_[i][j] += other.matrix_[i][j];
        }
      }
    }
    else{
      throw std::length_error("Amount of rows or cols are not equal");
    }
  }
}

double& S21Matrix::operator()(int i, int j) {
  if (i > this->rows_ || j > this->cols_ || i < 0 || j < 0) {
    throw std::length_error("Incorrect amount of cols");
  }
  return this->matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other){
  if(this->matrix_==nullptr || other.matrix_ == nullptr || (this->rows_<1 || other.rows_<1)){
    throw std::length_error("The matrix is incorrect");
  }
  else{
    if(this->rows_ == other.rows_){
      for (int i = 0; i < this->rows_; i++){
        for (int j = 0; j < this->cols_; j++){
          this->matrix_[i][j] -= other.matrix_[i][j];
        }
      }
    }
    else{
      throw std::length_error("Amount of rows or cols are not equal");
    }
  }
}

void S21Matrix::MulNumber(const double num){
  if(this->matrix_==nullptr || (this->rows_<1 || this->cols_<1)){
    throw std::length_error("The matrix is incorrect");
  }
  else{
      for (int i = 0; i < this->rows_; i++){
        for (int j = 0; j < this->cols_; j++){
          this->matrix_[i][j] *= num;
        }
      }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other){
  if(this->matrix_==nullptr || other.matrix_ == nullptr || (this->rows_<1 || other.rows_<1)){
    throw std::length_error("The matrix is incorrect");
  }
  else{
    if(this->cols_ == other.rows_){
      S21Matrix result(this->rows_, other.cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int a = 0; a < other.rows_; a++) {
          result.matrix_[i][j] += this->matrix_[i][a] * other.matrix_[a][j];
        }
      }
    }
    this->RemoveMatrix();
    this->CopyMatrix(result);
    }
    else{
      throw std::length_error("Amount of rows are not equal to cols");
    }
  }
}