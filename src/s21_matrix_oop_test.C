#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix mat;
  ASSERT_EQ(mat.getRows(), 0);
  ASSERT_EQ(mat.getCols(), 0);
  ASSERT_EQ(mat.getMatrix(), nullptr);
}
TEST(S21MatrixTest, Constructor) {
  S21Matrix mat(3, 4);
  ASSERT_EQ(mat.getRows(), 3);
  ASSERT_EQ(mat.getCols(), 4);
  ASSERT_NE(mat.getMatrix(), nullptr);

  for (int i = 0; i < mat.getRows(); i++) {
    for (int j = 0; j < mat.getCols(); j++) {
      ASSERT_EQ(mat.getMatrix()[i][j], 0);
    }
  }

  ASSERT_THROW(S21Matrix mat2(0, 4), std::length_error);
  ASSERT_THROW(S21Matrix mat3(3, -1), std::length_error);
}

TEST(S21MatrixTest, constructor_move) {
  S21Matrix A(5, 5);
  S21Matrix B(std::move(A));
  EXPECT_EQ(5, B.getRows());
  EXPECT_EQ(5, B.getCols());
  EXPECT_EQ(0, A.getRows());
  EXPECT_EQ(0, A.getCols());
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix A(3, 4);
  S21Matrix B(A);
  EXPECT_EQ(3, B.getRows());
  EXPECT_EQ(4, B.getCols());
  EXPECT_EQ(1, A == B);
}

TEST(S21MatrixTest, SumMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 6;
  expected(0, 1) = 8;
  expected(1, 0) = 10;
  expected(1, 1) = 12;

  a.SumMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, EqTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(Test, EQmatrix) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A == B, std::length_error);
}

TEST(S21MatrixTest, SubMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 4;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 6;

  b(0, 0) = 2;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 3;

  expected(0, 0) = 2;
  expected(0, 1) = 2;
  expected(1, 0) = 3;
  expected(1, 1) = 3;

  a.SubMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, MulNumberTest) {
  S21Matrix a(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  expected(0, 0) = 2;
  expected(0, 1) = 4;
  expected(1, 0) = 6;
  expected(1, 1) = 8;

  a.MulNumber(2);

  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, MulMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 19;
  expected(0, 1) = 22;
  expected(1, 0) = 43;
  expected(1, 1) = 50;

  a.MulMatrix(b);

  EXPECT_TRUE(a == expected);
}

TEST(Test, operator_minus) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix C(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  C(0, 0) = 0;
  C(0, 1) = 0;
  C(1, 0) = 0;
  C(1, 1) = 0;
  A(0, 0) = 2;
  A(0, 1) = 4;
  A(1, 0) = 6;
  A(1, 1) = 8;
  C = A - B;
  EXPECT_EQ(1, C == B);
}

TEST(Test, operator_plus) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix C(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  C(0, 0) = 0;
  C(0, 1) = 0;
  C(1, 0) = 0;
  C(1, 1) = 0;
  A(0, 0) = 2;
  A(0, 1) = 4;
  A(1, 0) = 6;
  A(1, 1) = 8;
  C = B + B;
  EXPECT_EQ(1, A == C);
}

TEST(Test, operator_pluseq) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A += B;
  EXPECT_EQ(1, A == B);
}
TEST(Test, operator_minuseq) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 4;
  A(1, 0) = 5;
  A(1, 1) = 6;
  A(1, 2) = 7;
  A(1, 3) = 8;
  A(2, 0) = 9;
  A(2, 1) = 10;
  A(2, 2) = 11;
  A(2, 3) = 12;
  A -= B;
  B -= B;
  EXPECT_EQ(1, A == B);
}
TEST(Test, operator_mulNumbereq) {
  S21Matrix B(3, 4);
  S21Matrix A(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 2;
  A(0, 1) = 4;
  A(0, 2) = 6;
  A(0, 3) = 8;
  A(1, 0) = 10;
  A(1, 1) = 12;
  A(1, 2) = 14;
  A(1, 3) = 16;
  A(2, 0) = 18;
  A(2, 1) = 20;
  A(2, 2) = 22;
  A(2, 3) = 24;

  B *= 2;
  EXPECT_EQ(1, B == A);
}
TEST(Test, operator_mulMatrixeq) {
  S21Matrix B(2, 2);
  S21Matrix A(2, 2);
  S21Matrix expected(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  expected(0, 0) = 11;
  expected(0, 1) = 14;
  expected(1, 0) = 35;
  expected(1, 1) = 46;

  B *= A;
  EXPECT_EQ(1, B == expected);
}
TEST(Test, operator_mulMatrix) {
  S21Matrix B(2, 2);
  S21Matrix A(2, 2);
  S21Matrix expected(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;  ///
  A(1, 1) = 6;

  expected(0, 0) = 11;
  expected(0, 1) = 14;
  expected(1, 0) = 35;
  expected(1, 1) = 46;

  B = B * A;
  EXPECT_EQ(1, B == expected);
}
TEST(Test, operator_mulNumber) {
  S21Matrix B(3, 4);
  S21Matrix A(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 2;
  A(0, 1) = 4;
  A(0, 2) = 6;
  A(0, 3) = 8;
  A(1, 0) = 10;
  A(1, 1) = 12;
  A(1, 2) = 14;
  A(1, 3) = 16;
  A(2, 0) = 18;
  A(2, 1) = 20;
  A(2, 2) = 22;
  A(2, 3) = 24;

  B = B * 2;
  EXPECT_EQ(1, B == A);
}

TEST(Test, Det1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 4;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;
  EXPECT_EQ(A.Determinant(), 12);
}

TEST(Test, Det2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = -2;
  A(1, 0) = 4.22;
  A(1, 1) = 4.5;
  EXPECT_EQ(A.Determinant(), 12.94);
}

TEST(Test, Det3) {
  S21Matrix A(2, 2);
  A(0, 0) = 6;
  A(0, 1) = -2;
  A(1, 0) = 4;
  A(1, 1) = 4.5;
  EXPECT_EQ(A.Determinant(), 35);
}

TEST(Test, Calc1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 2;
  A(0, 1) = 3;
  A(1, 0) = 1;
  A(1, 1) = 6;
  B(0, 0) = 6;
  B(0, 1) = -1;
  B(1, 0) = -3;
  B(1, 1) = 2;
  EXPECT_EQ(A.CalcComplements() == B, 1);
}

TEST(Test, Error1) {
  S21Matrix A;
  EXPECT_THROW(A.CalcComplements(), std::length_error);
}
TEST(Test, Error2) {
  S21Matrix A;
  EXPECT_THROW(A.Determinant(), std::length_error);
}
TEST(Test, Error3) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}
TEST(Test, Error4) {
  S21Matrix A;
  EXPECT_THROW(A.Transpose(), std::length_error);
}
TEST(Test, Error5) {
  S21Matrix A;
  EXPECT_THROW(A.CalcComplements(), std::length_error);
}
TEST(Test, Error6) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}

TEST(Test, Inverse) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = -2;
  B(0, 1) = 1;
  B(1, 0) = 1.5;
  B(1, 1) = -0.5;
  EXPECT_EQ(A.InverseMatrix() == B, 1);
}

TEST(Test, Error7) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A.SumMatrix(B), std::length_error);
}
TEST(Test, Error8) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A.SubMatrix(B), std::length_error);
}
TEST(Test, SetColsError) {
  S21Matrix A;
  EXPECT_THROW(A.SetCols(0), std::length_error);
}
TEST(Test, SetRowsError) {
  S21Matrix A;
  EXPECT_THROW(A.SetRows(0), std::length_error);
}
TEST(Test, SetCols) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 2);
  A.SetCols(2);
  EXPECT_EQ(A.getCols(), B.getCols());
}
TEST(Test, SetRows) {
  S21Matrix A(1, 1);
  S21Matrix B(2, 1);
  A.SetRows(2);
  EXPECT_EQ(A.getRows(), B.getRows());
}
TEST(Test, operator_error) {
  S21Matrix B(2, 2);
  EXPECT_THROW((B(0, 5) = 2), std::length_error);
}
TEST(Test, OperatorConst) {
  const S21Matrix A(1, 1);
  A(0, 0) = 1;
  EXPECT_EQ(A(0, 0), 1);
}
TEST(Test, OperatorConstError) {
  const S21Matrix A(1, 1);
  EXPECT_THROW((A(0, 5) = 1), std::length_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}