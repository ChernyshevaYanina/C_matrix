#include <check.h>
#include <stdbool.h>

#include "matrix.h"

#define ACC 0.00000009

#define EPS 1e-7

// OK
#define RESULT_OK 0

// Ошибка, некорректная матрица
#define INCORRECT_MATRIX 1

// Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)
#define CALCULATION_ERROR 2

int fill(matrix_t *A, double n);
bool valid_matrix(matrix_t *m);
bool compatible_matrix(matrix_t *A, matrix_t *B);

int fill(matrix_t *result, double n) {
  int res = RESULT_OK;
  if (valid_matrix(result)) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = n;
      }
    }
  }
  return res;
}

bool valid_matrix(matrix_t *m) {
  bool res = true;
  if (m && m->matrix != NULL && m->columns >= 1 && m->rows >= 1) {
    for (int i = 0; i < m->rows; i++) {
    }
  }
  return res;
}

START_TEST(eq_matrix_test_1) {
  matrix_t A = {0};
  create_matrix(41, 41, &A);
  matrix_t B = {0};
  create_matrix(41, 41, &B);
  fill(&A, 1);
  fill(&B, 1);
  int expected_result = SUCCESS;
  int actual_result = eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t A = {0};
  create_matrix(83, 83, &A);
  matrix_t B = {0};
  create_matrix(83, 83, &B);
  fill(&A, 7);
  fill(&B, 9);
  int expected_result = FAILURE;
  int actual_result = eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  matrix_t A = {0};
  create_matrix(32, 32, &A);
  matrix_t B = {0};
  create_matrix(27, 27, &B);
  fill(&A, 42);
  fill(&B, 42);
  int expected_result = FAILURE;
  int actual_result = eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_4) {
  matrix_t A = {0};
  create_matrix(22, 22, &A);
  matrix_t B = {0};
  create_matrix(22, 22, &B);
  fill(&A, 13);
  fill(&B, 13);
  // A.matrix_type = INCORRECT_MATRIX;
  int expected_result = SUCCESS;
  int actual_result = eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_test_1) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  matrix_t B = {0};
  create_matrix(4, 4, &B);
  fill(&A, 3);
  fill(&B, 4);

  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);
  fill(&expected_result, 7);
  matrix_t actual_result = {0};
  sum_matrix(&A, &B, &actual_result);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }
  // ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(sum_matrix_test_2) {
  matrix_t A = {0};
  create_matrix(2, 2, &A);
  matrix_t B = {0};
  create_matrix(4, 4, &B);
  matrix_t expected_result = {0};
  create_matrix(2, 2, &expected_result);

  matrix_t actual_result = {0};
  sum_matrix(&A, &B, &actual_result);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(sum_matrix_test_3) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  matrix_t B = {0};
  create_matrix(4, 4, &B);
  B.matrix[0][0] = 1;
  B.matrix[1][1] = 1;
  B.matrix[2][2] = 1;
  B.matrix[3][3] = 1;
  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);
  expected_result.matrix[0][0] = 1;
  expected_result.matrix[1][1] = 1;
  expected_result.matrix[2][2] = 1;
  expected_result.matrix[3][3] = 1;
  // expected_result.matrix_type = IDENTITY_MATRIX;
  matrix_t actual_result = {0};
  sum_matrix(&A, &B, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }
  // ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(sub_matrix_test_1) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  matrix_t B = {0};
  create_matrix(4, 4, &B);
  fill(&A, 6);
  fill(&B, 4);
  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);
  fill(&expected_result, 2);
  matrix_t actual_result = {0};
  sub_matrix(&A, &B, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(sub_matrix_test_2) {
  matrix_t A = {0};
  create_matrix(2, 2, &A);
  matrix_t B = {0};
  create_matrix(4, 4, &B);
  matrix_t expected_result = {0};
  create_matrix(2, 2, &expected_result);

  matrix_t actual_result = {0};
  sub_matrix(&A, &B, &actual_result);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(mult_number_test_1) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  fill(&A, 3);
  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);
  fill(&expected_result, 30);
  matrix_t actual_result = {0};
  mult_number(&A, 10, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t A = {0};
  create_matrix(2, 2, &A);

  matrix_t expected_result = {0};
  create_matrix(2, 2, &expected_result);

  matrix_t actual_result = {0};
  mult_number(&A, 3, &actual_result);

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(mult_matrix_test_1) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  matrix_t B = {0};
  create_matrix(4, 4, &B);
  fill(&A, 3);
  fill(&B, 3);
  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);
  fill(&expected_result, 36);
  matrix_t actual_result = {0};
  mult_matrix(&A, &B, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  matrix_t B = {0};
  create_matrix(3, 3, &B);
  fill(&A, 3);
  fill(&B, 3);
  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);

  matrix_t actual_result = {0};
  int res = mult_matrix(&A, &B, &actual_result);
  ck_assert(res == INCORRECT_MATRIX || res == CALCULATION_ERROR);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(transpose_test_1) {
  matrix_t A = {0};
  create_matrix(4, 4, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;

  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 4;

  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;
  A.matrix[2][3] = 4;

  A.matrix[3][0] = 1;
  A.matrix[3][1] = 2;
  A.matrix[3][2] = 3;
  A.matrix[3][3] = 4;

  matrix_t expected_result = {0};
  create_matrix(4, 4, &expected_result);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      expected_result.matrix[j][i] = A.matrix[i][j];
    }
  }

  matrix_t actual_result = {0};
  transpose(&A, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(transpose_test_2) {
  matrix_t A = {0};
  create_matrix(6, 2, &A);

  matrix_t expected_result = {0};
  create_matrix(2, 6, &expected_result);

  matrix_t actual_result = {0};
  transpose(&A, &actual_result);

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(calc_complements_test_1) {
  matrix_t A = {0};
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  matrix_t expected_result = {0};
  create_matrix(3, 3, &expected_result);

  expected_result.matrix[0][0] = 0;
  expected_result.matrix[0][1] = 10;
  expected_result.matrix[0][2] = -20;

  expected_result.matrix[1][0] = 4;
  expected_result.matrix[1][1] = -14;
  expected_result.matrix[1][2] = 8;

  expected_result.matrix[2][0] = -8;
  expected_result.matrix[2][1] = -2;
  expected_result.matrix[2][2] = 4;

  matrix_t actual_result = {0};
  calc_complements(&A, &actual_result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(calc_complements_test_2) {
  matrix_t A = {0};
  create_matrix(3, 4, &A);

  matrix_t expected_result = {0};
  create_matrix(3, 4, &expected_result);

  matrix_t actual_result = {0};
  calc_complements(&A, &actual_result);

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(determinant_test_1) {
  matrix_t A = {0};
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  double expected_result = 0;
  double actual_result = 0;
  determinant(&A, &actual_result);

  ck_assert(fabsl(expected_result - actual_result) < ACC);
  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t A = {0};
  create_matrix(3, 4, &A);
  double actual_result = 0;
  determinant(&A, &actual_result);

  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_1) {
  matrix_t A;
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  matrix_t expected_result;
  create_matrix(3, 3, &expected_result);

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;
  expected_result.matrix[0][2] = 1;

  expected_result.matrix[1][0] = -38;
  expected_result.matrix[1][1] = 41;
  expected_result.matrix[1][2] = -34;

  expected_result.matrix[2][0] = 27;
  expected_result.matrix[2][1] = -29;
  expected_result.matrix[2][2] = 24;

  matrix_t actual_result;
  inverse_matrix(&A, &actual_result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t A;
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  matrix_t expected_result;
  create_matrix(3, 3, &expected_result);

  matrix_t actual_result;
  inverse_matrix(&A, &actual_result);

  remove_matrix(&A);
  remove_matrix(&expected_result);
}
END_TEST

START_TEST(create_matrix_test_1) {
  matrix_t actual_result;
  int res = create_matrix(-88, -88, &actual_result);

  ck_assert(res == CALCULATION_ERROR || res == INCORRECT_MATRIX);
}
END_TEST

START_TEST(valid_matrix_test_1) {
  matrix_t actual_result;
  int res = create_matrix(100, 100, &actual_result);

  ck_assert(res == RESULT_OK);
  ck_assert(valid_matrix(&actual_result) == true);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  matrix_t A;
  create_matrix(2, 2, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;

  A.matrix[1][0] = 1;
  A.matrix[1][1] = 4;

  matrix_t expected_result;
  create_matrix(2, 2, &expected_result);

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;

  expected_result.matrix[1][0] = -0.25;
  expected_result.matrix[1][1] = 0.5;

  matrix_t actual_result;
  inverse_matrix(&A, &actual_result);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert(fabsl(expected_result.matrix[i][j] -
                      actual_result.matrix[i][j]) < ACC);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  matrix_t A;
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;

  matrix_t expected_result;
  create_matrix(1, 1, &expected_result);

  expected_result.matrix[0][0] = 1;

  matrix_t actual_result;
  inverse_matrix(&A, &actual_result);

  ck_assert(fabsl(expected_result.matrix[0][0] - actual_result.matrix[0][0]) <
            ACC);

  remove_matrix(&A);
  remove_matrix(&expected_result);
  remove_matrix(&actual_result);
}
END_TEST

START_TEST(test2_create_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  int result = create_matrix(3, 2, &matrix);

  ck_assert_int_eq(matrix.rows, 3);
  ck_assert_int_eq(matrix.columns, 2);
  ck_assert_int_eq(result, 0);

  remove_matrix(&matrix);
  result = create_matrix(3, 0, &matrix);

  ck_assert_int_eq(result, 1);
  remove_matrix(&matrix);
}
END_TEST

START_TEST(test2_eq_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  create_matrix(3, 3, &matrix);
  create_matrix(3, 3, &matrix2);
  create_matrix(3, 4, &matrix3);

  int count = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = ++count + 1.01234567;
      matrix2.matrix[i][j] = count + 1.01234567;
      matrix3.matrix[i][j] = count + 1.01234567;
    }
  }

  int result = eq_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, 1);

  matrix2.matrix[2][2] += 0.0000009;

  result = eq_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, 0);

  result = eq_matrix(&matrix, &matrix3);

  ck_assert_int_eq(result, 0);

  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
}
END_TEST

START_TEST(test2_sum_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};
  matrix_t matrix4 = {NULL, 0, 0};

  create_matrix(2, 2, &matrix);
  create_matrix(2, 2, &matrix2);
  create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter;
      matrix2.matrix[i][j] = counter;
      matrix3.matrix[i][j] = counter++;
    }
  }

  int result = sum_matrix(&matrix, &matrix2, &matrix4);

  ck_assert_int_eq(matrix4.matrix[0][0], 2);
  ck_assert_int_eq(matrix4.matrix[0][1], 4);
  ck_assert_int_eq(matrix4.matrix[1][0], 6);
  ck_assert_int_eq(matrix4.matrix[1][1], 8);
  ck_assert_int_eq(result, 0);

  remove_matrix(&matrix4);

  result = sum_matrix(&matrix, &matrix3, &matrix4);

  ck_assert_int_eq(result, 2);

  matrix3.rows = 0;

  remove_matrix(&matrix4);

  result = sum_matrix(&matrix, &matrix3, &matrix4);

  ck_assert_int_eq(result, 1);

  matrix3.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
  remove_matrix(&matrix4);
}
END_TEST

START_TEST(test2_sub_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};
  matrix_t matrix4 = {NULL, 0, 0};

  create_matrix(2, 2, &matrix);
  create_matrix(2, 2, &matrix2);
  create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = 0;
      matrix2.matrix[i][j] = counter;
      matrix3.matrix[i][j] = counter++;
    }
  }

  int result = sub_matrix(&matrix, &matrix2, &matrix4);

  ck_assert_int_eq(matrix4.matrix[0][0], -1);
  ck_assert_int_eq(matrix4.matrix[0][1], -2);
  ck_assert_int_eq(matrix4.matrix[1][0], -3);
  ck_assert_int_eq(matrix4.matrix[1][1], -4);
  ck_assert_int_eq(result, 0);

  remove_matrix(&matrix4);

  result = sub_matrix(&matrix, &matrix3, &matrix4);

  ck_assert_int_eq(result, 2);

  matrix3.rows = 0;

  remove_matrix(&matrix4);

  result = sub_matrix(&matrix, &matrix3, &matrix4);

  ck_assert_int_eq(result, 1);

  matrix3.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
  remove_matrix(&matrix4);
}
END_TEST

START_TEST(test2_mult_number) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  create_matrix(2, 2, &matrix);
  create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  double test_number = 0.5;
  int result = mult_number(&matrix, test_number, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][1], 1);
  ck_assert_int_eq(matrix2.matrix[1][1], 2);
  ck_assert_int_eq(result, 0);

  remove_matrix(&matrix2);

  result = mult_number(&matrix3, test_number, &matrix2);

  ck_assert_int_eq(result, 0);

  matrix3.rows = 0;

  remove_matrix(&matrix2);

  result = mult_number(&matrix3, test_number, &matrix2);

  ck_assert_int_eq(result, 1);
  matrix3.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
}
END_TEST

START_TEST(test2_mult_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  create_matrix(2, 2, &matrix);
  create_matrix(2, 2, &matrix2);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter;
      matrix2.matrix[i][j] = counter++;
    }
  }

  int result = mult_matrix(&matrix, &matrix2, &matrix3);

  ck_assert_int_eq(matrix3.matrix[0][0], 7);
  ck_assert_int_eq(matrix3.matrix[0][1], 10);
  ck_assert_int_eq(matrix3.matrix[1][0], 15);
  ck_assert_int_eq(matrix3.matrix[1][1], 22);
  ck_assert_int_eq(result, 0);

  matrix.columns = 1;

  remove_matrix(&matrix3);

  result = mult_matrix(&matrix, &matrix2, &matrix3);

  ck_assert_int_eq(result, 2);

  matrix.rows = 0;

  remove_matrix(&matrix3);

  result = mult_matrix(&matrix, &matrix2, &matrix3);

  ck_assert_int_eq(result, 1);

  matrix.rows = 2;
  matrix.columns = 2;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
}
END_TEST

START_TEST(test2_transpose) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  create_matrix(2, 2, &matrix);
  create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  int result = transpose(&matrix, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][0], 1);
  ck_assert_int_eq(matrix2.matrix[0][1], 3);
  ck_assert_int_eq(matrix2.matrix[1][0], 2);
  ck_assert_int_eq(matrix2.matrix[1][1], 4);
  ck_assert_int_eq(result, 0);

  remove_matrix(&matrix2);

  matrix3.rows = 0;

  result = transpose(&matrix3, &matrix2);

  ck_assert_int_eq(result, 1);

  matrix3.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
}
END_TEST

START_TEST(test2_calc_complements) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  create_matrix(3, 3, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  int result = calc_complements(&matrix, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][0], 0);
  ck_assert_int_eq(matrix2.matrix[0][1], 10);
  ck_assert_int_eq(matrix2.matrix[0][2], -20);
  ck_assert_int_eq(matrix2.matrix[1][0], 4);
  ck_assert_int_eq(matrix2.matrix[1][1], -14);
  ck_assert_int_eq(matrix2.matrix[1][2], 8);
  ck_assert_int_eq(matrix2.matrix[2][0], -8);
  ck_assert_int_eq(matrix2.matrix[2][1], -2);
  ck_assert_int_eq(matrix2.matrix[2][2], 4);
  ck_assert_int_eq(result, 0);

  matrix.columns = 1;

  remove_matrix(&matrix2);

  result = calc_complements(&matrix, &matrix2);

  ck_assert_int_eq(result, 2);

  matrix.rows = 0;

  remove_matrix(&matrix2);

  result = calc_complements(&matrix, &matrix2);

  ck_assert_int_eq(result, 1);
  matrix.columns = 3;
  matrix.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(test2_determinant) {
  double determinant_value = 0;
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  create_matrix(3, 3, &matrix);
  create_matrix(3, 2, &matrix2);

  int counter = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  int result = determinant(&matrix, &determinant_value);
  ck_assert_int_eq(determinant_value, 0);
  ck_assert_int_eq(result, 0);

  determinant_value = 0;

  result = determinant(&matrix2, &determinant_value);

  ck_assert_int_eq(result, 2);

  matrix2.rows = 0;
  determinant_value = 0;

  result = determinant(&matrix2, &determinant_value);

  ck_assert_int_eq(result, 1);
  matrix2.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(test2_determinant_2) {
  double determinant_value = 0;
  matrix_t matrix = {NULL, 0, 0};

  create_matrix(4, 4, &matrix);

  matrix.matrix[0][0] = 9;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 2;
  matrix.matrix[0][3] = 4;

  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 4;
  matrix.matrix[1][3] = 4;

  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 4;
  matrix.matrix[2][2] = 9;
  matrix.matrix[2][3] = 9;

  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = 1;
  matrix.matrix[3][2] = 5;
  matrix.matrix[3][3] = 1;

  int result = determinant(&matrix, &determinant_value);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(determinant_value, -578);

  remove_matrix(&matrix);
}
END_TEST

START_TEST(test2_determinant_3) {
  double determinant_value = 0;
  matrix_t matrix2 = {NULL, 0, 0};
  create_matrix(1, 1, &matrix2);

  matrix2.matrix[0][0] = 10;
  int result = determinant(&matrix2, &determinant_value);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(determinant_value, 10);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(test2_inverse_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  create_matrix(3, 3, &matrix);

  matrix.matrix[0][0] = 4;
  matrix.matrix[0][1] = -2;
  matrix.matrix[0][2] = 1;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 6;
  matrix.matrix[1][2] = -2;
  matrix.matrix[2][0] = 1;
  matrix.matrix[2][1] = 0;
  matrix.matrix[2][2] = 0;

  int result = inverse_matrix(&matrix, &matrix2);
  ck_assert_int_eq(matrix2.matrix[0][1], 0);
  ck_assert_int_eq(matrix2.matrix[0][2], 1);
  ck_assert_int_eq(matrix2.matrix[1][0], 1);
  ck_assert_int_eq(matrix2.matrix[2][0], 3);
  ck_assert_int_eq(matrix2.matrix[2][1], 1);
  ck_assert_int_eq(matrix2.matrix[2][2], -13);
  ck_assert_int_eq(result, 0);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 4;
  matrix.matrix[0][2] = 1;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 3;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  remove_matrix(&matrix2);

  result = inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, 2);

  matrix.rows = 2;

  remove_matrix(&matrix2);

  result = inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, 2);

  matrix.rows = 0;

  remove_matrix(&matrix2);

  result = inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, 1);
  matrix.rows = 3;
  remove_matrix(&matrix);
  remove_matrix(&matrix2);
#define OK 0
#define ERROR 2
}
END_TEST

START_TEST(test3_create_matrix) {
  matrix_t my_matrix;
  int ret = create_matrix(4, 4, &my_matrix);
  ck_assert_int_eq(ret, 0);
  remove_matrix(&my_matrix);

  ret = create_matrix(-4, 4, &my_matrix);
  ck_assert_int_eq(ret, 1);

  ret = create_matrix(-4, 0, &my_matrix);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test3_eq_matrix) {
  matrix_t matrix_1 = {0}, matrix_2 = {0};
  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  int ret = eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 4, &matrix_1);
  create_matrix(10, 10, &matrix_2);
  ret = eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 0);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  matrix_1.matrix[2][3] = -7;
  ret = eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 0);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  matrix_1.matrix[2][3] = -7;
  matrix_2.matrix[2][3] = -7;
  ret = eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test3_sum_matrix) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  create_matrix(4, 4, &res_org);
  int ret = sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
  remove_matrix(&res_my);
  remove_matrix(&res_org);

  create_matrix(4, 5, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  ret = sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 5, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  ret = sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  ret = sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
  remove_matrix(&res_my);
  remove_matrix(&res_org);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * 2;
    }
  }
  ret = sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
  remove_matrix(&res_my);
  remove_matrix(&res_org);
}
END_TEST

START_TEST(test3_sub_matrix) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  create_matrix(4, 4, &res_org);
  int ret = sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
  remove_matrix(&res_my);
  remove_matrix(&res_org);

  create_matrix(4, 5, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  ret = sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 4, &matrix_2);
  ret = sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  ret = sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
  remove_matrix(&res_my);
  remove_matrix(&res_org);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &matrix_2);
  create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
    }
  }
  ret = sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&matrix_2);
  remove_matrix(&res_my);
  remove_matrix(&res_org);
}
END_TEST

START_TEST(test3_mult_number) {
  matrix_t matrix_1, res_my, res_org;
  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &res_org);
  int ret = mult_number(&matrix_1, 5, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&res_my);
  remove_matrix(&res_org);

  create_matrix(4, 4, &matrix_1);
  create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * (-3);
    }
  }
  ret = mult_number(&matrix_1, -3, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&res_my);
  remove_matrix(&res_org);

  create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
    }
  }
  ret = mult_number(&matrix_1, 0, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix_1);
  remove_matrix(&res_my);
  remove_matrix(&res_org);
}
END_TEST

START_TEST(test3_mult_matrix) {
  matrix_t mat_1, mat_2, res_mat, res_org;

  create_matrix(2, 2, &mat_1);
  create_matrix(2, 2, &mat_2);
  create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = i + j + 1;
      mat_2.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int ret = mult_matrix(&mat_1, &mat_2, &res_mat);

  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&mat_1);
  remove_matrix(&mat_2);
  remove_matrix(&res_mat);
  remove_matrix(&res_org);

  create_matrix(3, 2, &mat_1);
  create_matrix(2, 2, &mat_2);
  create_matrix(3, 2, &res_org);
  ret = mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&mat_1);
  remove_matrix(&mat_2);
  remove_matrix(&res_mat);
  remove_matrix(&res_org);

  create_matrix(2, 7, &mat_1);
  create_matrix(2, 2, &mat_2);
  ret = mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 2);
  remove_matrix(&mat_1);
  remove_matrix(&mat_2);
}
END_TEST

START_TEST(test3_transpose) {
  matrix_t mat_1, res_mat, res_org;

  create_matrix(2, 2, &mat_1);
  create_matrix(2, 2, &res_org);
  mat_1.matrix[0][0] = 1;
  mat_1.matrix[0][1] = 2;
  mat_1.matrix[1][0] = 3;
  mat_1.matrix[1][1] = 4;
  res_org.matrix[0][0] = 1;
  res_org.matrix[0][1] = 3;
  res_org.matrix[1][0] = 2;
  res_org.matrix[1][1] = 4;
  int ret = transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&mat_1);
  remove_matrix(&res_mat);
  remove_matrix(&res_org);

  double matrix[2][2] = {
      {1, 2},
      {3, 4},
  };
  double res[2][2] = {{1, 3}, {2, 4}};
  create_matrix(2, 2, &mat_1);
  create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      res_org.matrix[i][j] = res[i][j];
    }
  }
  ret = transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&mat_1);
  remove_matrix(&res_mat);
  remove_matrix(&res_org);
}
END_TEST

START_TEST(test3_determinant) {
  matrix_t matrix;
  create_matrix(3, 3, &matrix);
  int count = 1;
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = count++;
    }
  }
  matrix.matrix[2][2] = 10;
  double res = 0;
  int ret = determinant(&matrix, &res);
  ck_assert_uint_eq(res, -3);
  ck_assert_int_eq(ret, 0);
  remove_matrix(&matrix);
}
END_TEST

START_TEST(test3_calc_complements) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  create_matrix(3, 3, &matrix);
  create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix);
  remove_matrix(&res_my);
  remove_matrix(&res_org);
}
END_TEST

START_TEST(test3_inverse_matrix) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  create_matrix(3, 3, &matrix);
  create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  remove_matrix(&matrix);
  remove_matrix(&res_my);
  remove_matrix(&res_org);
}
END_TEST

START_TEST(test4_create_1) {
  matrix_t A = {0};
  create_matrix(3, 4, &A);
  int res = 1, res1 = 1;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      if (A.matrix[i][j] != 0.0) {
        res = 0;
      }
    }
  }

  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(res1, 1);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 4);
  remove_matrix(&A);
}
END_TEST

START_TEST(test4_create_2) {
  matrix_t A = {0};
  int r = create_matrix(0, -1, &A);
  int res = 1;
  if (r != INCORRECT_MATRIX) {
    res = 0;
  }
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(test4_create_3) {
  matrix_t a = {0};
  int r = create_matrix(1, 1, &a);
  ck_assert_int_eq(r, 0);
  matrix_t a1 = {0};
  int r1 = create_matrix(-1, -2, &a1);
  ck_assert_int_eq(r1, INCORRECT_MATRIX);
  remove_matrix(&a);
}
END_TEST

START_TEST(test4_rem_1) {
  matrix_t a = {0};
  create_matrix(1, 1, &a);
  remove_matrix(&a);
  ck_assert_int_eq(a.rows, FAILURE);
  ck_assert_int_eq(a.columns, FAILURE);
}
END_TEST

START_TEST(test4_eq_1) {
  matrix_t A = {0}, B = {0}, C = {0}, D = {0};
  create_matrix(2, 3, &A);
  create_matrix(2, 3, &B);
  create_matrix(2, 3, &C);
  create_matrix(1, 3, &D);
  A.matrix[0][0] = 1.3455;
  A.matrix[0][1] = 4.2;
  A.matrix[0][2] = 3.4334;
  A.matrix[1][0] = 2.33;
  A.matrix[1][1] = 5.345;
  A.matrix[1][2] = 6.1;
  // r = 0;
  B.matrix[0][0] = 1.3455;
  B.matrix[0][1] = 4.2;
  B.matrix[0][2] = 3.4334;
  B.matrix[1][0] = 2.33;
  B.matrix[1][1] = 5.345;
  B.matrix[1][2] = 6.1;
  // B.matrix_type = 0;
  C.matrix[0][0] = 1.345;
  C.matrix[0][1] = 4.2;
  C.matrix[0][2] = 3.4334;
  C.matrix[1][0] = 2.33;
  C.matrix[1][1] = 5.345;
  C.matrix[1][2] = 6.1;
  // C.matrix_type
  D.matrix[0][0] = 1.35;
  D.matrix[0][1] = 4.2;
  D.matrix[0][2] = 3.44;
  // D.matrix_type = 0;
  int res = eq_matrix(&A, &B);
  int res1 = eq_matrix(&A, &C);
  int res2 = eq_matrix(&A, &D);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(res1, 0);
  ck_assert_int_eq(res2, 0);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(test4_eq_2) {
  matrix_t a = {0};
  create_matrix(1, 1, &a);
  matrix_t b = {0};
  create_matrix(1, 1, &b);
  ck_assert_int_eq(eq_matrix(&a, &b), SUCCESS);
  a.matrix[0][0] = 2;
  ck_assert_int_eq(eq_matrix(&a, &b), FAILURE);
  b.matrix[0][0] = 2.000000001;
  ck_assert_int_eq(eq_matrix(&a, &b), SUCCESS);
  b.matrix[0][0] = 2.00000002;
  ck_assert_int_eq(eq_matrix(&a, &b), SUCCESS);
  matrix_t c = {0};
  create_matrix(2, 1, &c);
  c.matrix[0][0] = 2;
  ck_assert_int_eq(eq_matrix(&a, &c), FAILURE);
  matrix_t d = {0};
  create_matrix(1, 1, &d);
  d.matrix[0][0] = 2;
  // d.matrix_type = 2;
  ck_assert_int_eq(eq_matrix(&a, &d), 1);
  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&c);
  remove_matrix(&d);
}
END_TEST

START_TEST(test4_sum_2) {
  matrix_t a = {0};
  create_matrix(2, 2, &a);
  matrix_t b = {0};
  create_matrix(2, 2, &b);
  a.matrix[0][0] = 1;
  a.matrix[1][1] = 1;
  matrix_t c = {0};
  sum_matrix(&a, &b, &c);

  remove_matrix(&c);

  matrix_t d = {0};
  create_matrix(2, 3, &d);
  sum_matrix(&a, &d, &c);

  remove_matrix(&c);

  matrix_t f = {0};
  create_matrix(2, 2, &f);
  sum_matrix(&a, &f, &c);
  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&c);
  remove_matrix(&d);
  remove_matrix(&f);
}
END_TEST

START_TEST(test4_sub_1) {
  matrix_t A = {0}, B = {0}, C = {0}, D = {0}, E = {0}, F = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  create_matrix(3, 3, &C);
  create_matrix(2, 2, &E);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 2.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 2.0;
  // r = 0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = 0.0;
  B.matrix[2][0] = 0.0;
  B.matrix[2][1] = 0.0;
  B.matrix[2][2] = 1.0;
  // B.matrix_type = 0;
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = 0.0;
  C.matrix[0][2] = 0.0;
  C.matrix[1][0] = 0.0;
  C.matrix[1][1] = 1.0;
  C.matrix[1][2] = 0.0;
  C.matrix[2][0] = 0.0;
  C.matrix[2][1] = 0.0;
  C.matrix[2][2] = 1.0;
  // C.matrix_type = 2;
  sub_matrix(&A, &B, &D);
  sub_matrix(&A, &E, &F);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
}
END_TEST

START_TEST(test4_sub_2) {
  matrix_t A = {0}, B = {0}, C = {0}, D = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  create_matrix(3, 3, &C);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = -1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = -1.0;
  // r = 0;
  B.matrix[0][0] = -1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = -1.0;
  B.matrix[1][2] = 0.0;
  B.matrix[2][0] = 0.0;
  B.matrix[2][1] = 0.0;
  B.matrix[2][2] = -1.0;
  // B.matrix_type = 0;
  sub_matrix(&A, &B, &D);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  // ck_assert_int_eq(D.matrix_type, 3);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(test4_sub_3) {
  matrix_t a = {0};
  create_matrix(2, 2, &a);
  matrix_t b = {0};
  create_matrix(2, 2, &b);
  a.matrix[0][0] = 2;
  a.matrix[1][1] = 2;
  b.matrix[0][0] = 1;
  b.matrix[1][1] = 1;
  matrix_t c = {0};
  sub_matrix(&a, &b, &c);
  remove_matrix(&c);
  matrix_t d = {0};
  create_matrix(2, 3, &d);
  sub_matrix(&a, &d, &c);
  remove_matrix(&c);
  matrix_t f = {0};
  create_matrix(2, 2, &f);
  remove_matrix(&f);
  sub_matrix(&a, &f, &c);
  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&c);
  remove_matrix(&d);
}
END_TEST

START_TEST(test4_mult_num_1) {
  matrix_t A = {0}, B = {0}, D = {0};
  double x = 3.45;
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  // r = 0;
  B.matrix[0][0] = 10.3074063;
  B.matrix[0][1] = -18.44232;
  B.matrix[1][0] = 21.4935;
  B.matrix[1][1] = -13.55574;
  // B.matrix_type = 0;
  mult_number(&A, x, &D);
  int res = eq_matrix(&D, &B);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&D);
}
END_TEST

START_TEST(test4_mult_num_2) {
  matrix_t a = {0};
  create_matrix(2, 2, &a);
  matrix_t c = {0};
  a.matrix[0][0] = 1;
  a.matrix[1][1] = 1;
  mult_number(&a, 1, &c);
  remove_matrix(&c);
  mult_number(&a, 2, &c);
  int check = 0;
  for (int i = 0; i < c.rows; i++) {
    for (int j = 0; j < c.columns; j++) {
      if (c.matrix[i][j] != (a.matrix[i][j] * 2)) {
        check = 1;
        break;
      }
      if (check) {
        break;
      }
    }
  }
  remove_matrix(&c);
  ck_assert_int_eq(check, FAILURE);
  remove_matrix(&a);
  mult_number(&a, 2, &c);
  remove_matrix(&c);
}
END_TEST

START_TEST(test4_mult_m_1) {
  matrix_t A = {0}, B = {0}, C = {0}, D = {0}, E = {0}, F = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 4, &B);
  create_matrix(2, 4, &C);
  create_matrix(4, 2, &E);
  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  // r = 0;
  B.matrix[0][0] = 4.838;
  B.matrix[0][1] = 8.0987;
  B.matrix[0][2] = 8.09;
  B.matrix[0][3] = -987;
  B.matrix[1][0] = -8;
  B.matrix[1][1] = -0.921;
  B.matrix[1][2] = -0.91;
  B.matrix[1][3] = 21;
  // B.matrix_type = 0;
  C.matrix[0][0] = 57.219070052;
  C.matrix[0][1] = 29.1194110498;
  C.matrix[0][2] = 29.03461686;
  C.matrix[0][3] = -3061.072098;
  C.matrix[1][0] = 61.57434;
  C.matrix[1][1] = 54.0736942;
  C.matrix[1][2] = 53.976272;
  C.matrix[1][3] = -6231.5232;
  // C.matrix_type = 0;
  mult_matrix(&A, &B, &D);
  mult_matrix(&A, &E, &F);
  int res = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 1);
  // ck_assert_int_eq(C.matrix_type, 0);
  // ck_assert_int_eq(F.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
}
END_TEST

START_TEST(test4_mult_m_2) {
  matrix_t a = {0};
  create_matrix(3, 2, &a);
  matrix_t b = {0};
  create_matrix(2, 3, &b);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 4;
  a.matrix[1][0] = 2;
  a.matrix[1][1] = 5;
  a.matrix[2][0] = 3;
  a.matrix[2][1] = 6;
  b.matrix[0][0] = 1;
  b.matrix[0][1] = -1;
  b.matrix[0][2] = 1;
  b.matrix[1][0] = 2;
  b.matrix[1][1] = 3;
  b.matrix[1][2] = 4;
  matrix_t res = {0};
  create_matrix(3, 3, &res);
  res.matrix[0][0] = 9;
  res.matrix[0][1] = 11;
  res.matrix[0][2] = 17;
  res.matrix[1][0] = 12;
  res.matrix[1][1] = 13;
  res.matrix[1][2] = 22;
  res.matrix[2][0] = 15;
  res.matrix[2][1] = 15;
  res.matrix[2][2] = 27;
  matrix_t c = {0};
  mult_matrix(&a, &b, &c);
  int check = 0;
  for (int i = 0; i < c.rows; i++) {
    for (int j = 0; j < c.columns; j++) {
      if (c.matrix[i][j] != res.matrix[i][j]) {
        check = 1;
        break;
      }
      if (check) {
        break;
      }
    }
  }
  remove_matrix(&c);
  ck_assert_int_eq(check, FAILURE);
  remove_matrix(&a);
  // // // r = INCORRECT_MATRIX;
  mult_matrix(&a, &b, &c);

  remove_matrix(&c);
  remove_matrix(&b);
  remove_matrix(&res);
  matrix_t m1 = {0};
  create_matrix(3, 1, &m1);
  remove_matrix(&m1);

  matrix_t m2 = {0};
  create_matrix(2, 4, &m2);
  matrix_t m3 = {0};
  mult_matrix(&m1, &m2, &m3);

  remove_matrix(&m3);
  remove_matrix(&m2);
}
END_TEST

START_TEST(test4_trans_1) {
  matrix_t A = {0}, B = {0}, C = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &C);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 2.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 2.0;
  // r = 0;
  transpose(&A, &B);
  C.matrix[0][0] = 2.0;
  C.matrix[0][1] = 0.0;
  C.matrix[0][2] = 0.0;
  C.matrix[1][0] = 0.0;
  C.matrix[1][1] = 2.0;
  C.matrix[1][2] = 0.0;
  C.matrix[2][0] = 0.0;
  C.matrix[2][1] = 0.0;
  C.matrix[2][2] = 2.0;
  // C.matrix_type = 0;
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(test4_trans_2) {
  matrix_t a = {0};
  create_matrix(2, 1, &a);
  matrix_t b = {0};
  create_matrix(1, 2, &b);
  a.matrix[0][0] = 1;
  a.matrix[1][0] = 2;
  // r = 0;
  b.matrix[0][0] = 1;
  b.matrix[0][1] = 2;
  // b.matrix_type = 0;
  matrix_t c = {0};
  transpose(&a, &c);
  ck_assert_int_eq(eq_matrix(&b, &c), SUCCESS);
  remove_matrix(&c);
  remove_matrix(&a);
  // // // r = INCORRECT_MATRIX;
  transpose(&a, &c);
  ck_assert_int_eq(eq_matrix(&b, &c), FAILURE);
  remove_matrix(&c);
  remove_matrix(&b);
}
END_TEST

START_TEST(test4_calc_compl_1) {
  matrix_t A = {0}, B = {0}, C = {0}, D = {0}, E = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &C);
  create_matrix(2, 3, &D);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  // r = 0;
  calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[0][2] = -20.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  C.matrix[1][2] = 8.0;
  C.matrix[2][0] = -8.0;
  C.matrix[2][1] = -2.0;
  C.matrix[2][2] = 4.0;
  // C.matrix_type = 0;
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);

  calc_complements(&D, &E);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
}
END_TEST

START_TEST(test4_calc_compl_2) {
  matrix_t a = {0};
  create_matrix(3, 3, &a);
  matrix_t res = {0};
  create_matrix(3, 3, &res);
  matrix_t m = {0};
  res.matrix[0][0] = 0;
  res.matrix[0][1] = 10;
  res.matrix[0][2] = -20;
  res.matrix[1][0] = 4;
  res.matrix[1][1] = -14;
  res.matrix[1][2] = 8;
  res.matrix[2][0] = -8;
  res.matrix[2][1] = -2;
  res.matrix[2][2] = 4;
  // res.matrix_type = 0;
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  // r = 0;
  calc_complements(&a, &m);
  ck_assert_int_eq(eq_matrix(&res, &m), SUCCESS);
  remove_matrix(&m);
  remove_matrix(&a);
  // // // r = INCORRECT_MATRIX;
  calc_complements(&a, &m);
  ck_assert_int_eq(eq_matrix(&res, &m), FAILURE);
  remove_matrix(&m);
  remove_matrix(&res);
}
END_TEST

START_TEST(test4_determ_1) {
  matrix_t A = {0}, C = {0}, D = {0};
  create_matrix(2, 2, &A);
  create_matrix(1, 1, &C);
  create_matrix(3, 3, &D);

  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  // r = 0;

  // B.matrix_type = 0;
  C.matrix[0][0] = 2.32443;
  D.matrix[0][0] = 2.8;
  D.matrix[0][1] = 1.3;
  D.matrix[0][2] = 7.01;
  D.matrix[1][0] = -1.03;
  D.matrix[1][1] = -2.3;
  D.matrix[1][2] = 3.01;
  D.matrix[2][0] = 0;
  D.matrix[2][1] = -3;
  D.matrix[2][2] = 2;
  double res;
  determinant(&A, &res);
  fail_if(!(fabs(res - 21.5639979032) < ACC));
  double res1;
  determinant(&C, &res1);
  fail_if(!(fabs(res1 - 2.32443) < ACC));

  double res2 = 0;

  determinant(&D, &res2);
  fail_if(!(fabs(res2 - 36.7429) < ACC));
  remove_matrix(&A);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(test4_inverse_1) {
  matrix_t A = {0}, C = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  // C.matrix_type = 0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  // r = 0;
  matrix_t B = {0};
  inverse_matrix(&A, &B);
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(test4_inverse_2) {
  matrix_t A = {0}, B = {0}, C = {0}, D = {0}, E = {0}, F = {0}, G = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &C);
  create_matrix(2, 3, &D);
  create_matrix(2, 2, &F);
  C.matrix[0][0] = 44300.0 / 367429.0;
  C.matrix[0][1] = -236300.0 / 367429.0;
  C.matrix[0][2] = 200360.0 / 367429.0;
  C.matrix[1][0] = 20600.0 / 367429.0;
  C.matrix[1][1] = 56000.0 / 367429.0;
  C.matrix[1][2] = -156483.0 / 367429.0;
  C.matrix[2][0] = 30900.0 / 367429.0;
  C.matrix[2][1] = 84000.0 / 367429.0;
  C.matrix[2][2] = -51010.0 / 367429.0;
  // C.matrix_type = 0;
  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;
  // r = 0;
  inverse_matrix(&A, &B);
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  inverse_matrix(&D, &E);
  // ck_assert_int_eq(E.matrix_type, 1);
  inverse_matrix(&F, &G);
  // ck_assert_int_eq(G.matrix_type, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
  remove_matrix(&E);
  remove_matrix(&F);
  remove_matrix(&G);
}
END_TEST

START_TEST(test4_inverse_3) {
  matrix_t res = {0};
  create_matrix(3, 3, &res);
  res.matrix[0][0] = 1;
  res.matrix[0][1] = -2;
  res.matrix[0][2] = 1;
  res.matrix[1][0] = -2;
  res.matrix[1][1] = 2;
  res.matrix[1][2] = -0.5;
  res.matrix[2][0] = 1;
  res.matrix[2][1] = -0.5;
  res.matrix[2][2] = 0;
  // res.matrix_type = 0;

  matrix_t a = {0};
  create_matrix(3, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 4;
  a.matrix[1][0] = 2;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 6;
  a.matrix[2][0] = 4;
  a.matrix[2][1] = 6;
  a.matrix[2][2] = 8;
  // r = 0;

  matrix_t a_obr = {0};
  inverse_matrix(&a, &a_obr);

  ck_assert_int_eq(eq_matrix(&res, &a_obr), SUCCESS);
  // ck_assert_int_eq(a_obr.matrix_type, CORRECT_MATRIX);
  remove_matrix(&a_obr);

  // // r = INCORRECT_MATRIX;
  inverse_matrix(&a, &a_obr);
  // ck_assert_int_eq(a_obr.matrix_type, INCORRECT_MATRIX);

  remove_matrix(&a);
  remove_matrix(&res);
  remove_matrix(&a_obr);
}
END_TEST

START_TEST(test4_eq_matrix_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 1, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  int result = eq_matrix(&matrix1, &matrix2);
  fail_if(result != 0);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(test4_eq_matrix_2) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix2.matrix_type = CORRECT_MATRIX;
  int result = eq_matrix(&matrix1, &matrix2);
  fail_if(result != 0);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(test4_eq_matrix_3) {
  matrix_t matrix1 = {0};
  create_matrix(2, 3, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(2, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  int result = eq_matrix(&matrix1, &matrix2);
  fail_if(result != 0);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
}
END_TEST

START_TEST(test4_sum_matrix_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = 10.0;
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sum_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sum_matrix_2) {
  matrix_t matrix1 = {0};
  create_matrix(3, 1, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sum_matrix(&matrix1, &matrix2, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sum_matrix_4) {
  matrix_t matrix1 = {0};
  create_matrix(2, 2, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(2, 2, &matrix2);
  matrix1.matrix[0][0] = 0.3148823;
  matrix1.matrix[0][1] = 0.2274032;
  matrix1.matrix[1][0] = -0.0338093;
  matrix1.matrix[1][1] = 1.7671095;
  matrix2.matrix[0][0] = -0.1904982;
  matrix2.matrix[0][1] = 2.2972714;
  matrix2.matrix[1][0] = 0.2396589;
  matrix2.matrix[1][1] = 1.9473702;
  matrix_t expected = {0};
  create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 0.1243841;
  expected.matrix[0][1] = 2.5246746;
  expected.matrix[1][0] = 0.2058496;
  expected.matrix[1][1] = 3.7144797;
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sum_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sum_matrix_5) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(2, 2, &matrix2);
  matrix2.matrix[0][0] = -0.1904982;
  matrix2.matrix[0][1] = 2.2972714;
  matrix2.matrix[1][0] = 0.2396589;
  matrix2.matrix[1][1] = 1.9473702;
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sum_matrix(&matrix1, &matrix2, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sum_matrix_6) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
      matrix2.matrix[i][j] = -1 * (i * matrix1.columns + j + 1);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sum_matrix(&matrix1, &matrix2, &result);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sub_matrix_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  int temp = -10;
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = (temp += 2);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sub_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sub_matrix_2) {
  matrix_t matrix1 = {0};
  create_matrix(3, 2, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sub_matrix(&matrix1, &matrix2, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sub_matrix_4) {
  matrix_t matrix1 = {0};
  create_matrix(2, 2, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(2, 2, &matrix2);
  matrix1.matrix[0][0] = 0.3879963;
  matrix1.matrix[0][1] = -0.9465799;
  matrix1.matrix[1][0] = 2.8311106;
  matrix1.matrix[1][1] = 2.4766419;
  matrix2.matrix[0][0] = 2.9210337;
  matrix2.matrix[0][1] = 1.8139900;
  matrix2.matrix[1][0] = 1.7304636;
  matrix2.matrix[1][1] = 1.9015551;
  matrix_t expected = {0};
  create_matrix(2, 2, &expected);
  expected.matrix[0][0] = -2.5330374;
  expected.matrix[0][1] = -2.7605699;
  expected.matrix[1][0] = 1.100647;
  expected.matrix[1][1] = 0.5750868;
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sub_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_sub_matrix_5) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(2, 2, &matrix2);
  matrix2.matrix[0][0] = -0.1904982;
  matrix2.matrix[0][1] = 2.2972714;
  matrix2.matrix[1][0] = 0.2396589;
  matrix2.matrix[1][1] = 1.9473702;
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  sub_matrix(&matrix1, &matrix2, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_number_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  double number = 2;
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = (i * matrix1.columns + j + 1) * number;
    }
  }
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_number(&matrix1, number, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_number_2) {
  matrix_t matrix1 = {0};
  create_matrix(2, 3, &matrix1);
  matrix1.matrix[0][0] = 0.4244828;
  matrix1.matrix[0][1] = 0.2825884;
  matrix1.matrix[0][2] = -2.5368773;
  matrix1.matrix[1][0] = -1.2964430;
  matrix1.matrix[1][1] = 2.6818946;
  matrix1.matrix[1][2] = 2.6017167;
  double number = 2.528973;
  matrix_t expected = {0};
  create_matrix(2, 3, &expected);
  for (int i = 0; i < expected.rows; i++) {
    for (int j = 0; j < expected.columns; j++) {
      expected.matrix[i][j] = matrix1.matrix[i][j] * number;
    }
  }
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_number(&matrix1, number, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_number_3) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  double number = 2.528973;
  matrix_t result = {0};
  mult_number(&matrix1, number, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_number_4) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  double number = NAN;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_number(&matrix1, number, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_matrix_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 30;
  expected.matrix[0][1] = 24;
  expected.matrix[0][2] = 18;
  expected.matrix[1][0] = 84;
  expected.matrix[1][1] = 69;
  expected.matrix[1][2] = 54;
  expected.matrix[2][0] = 138;
  expected.matrix[2][1] = 114;
  expected.matrix[2][2] = 90;
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_matrix_2) {
  matrix_t matrix1 = {0};
  create_matrix(3, 1, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_matrix(&matrix1, &matrix2, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_matrix_3) {
  matrix_t matrix1 = {0};
  create_matrix(2, 3, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 1, &matrix2);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  matrix_t expected = {0};
  create_matrix(2, 1, &expected);
  expected.matrix[0][0] = 10;
  expected.matrix[1][0] = 28;
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_matrix_4) {
  matrix_t matrix1 = {0};
  create_matrix(2, 2, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(2, 2, &matrix2);
  matrix1.matrix[0][0] = 0.4800344;
  matrix1.matrix[0][1] = -2.0621914;
  matrix1.matrix[1][0] = 2.7496997;
  matrix1.matrix[1][1] = 2.2021934;
  matrix2.matrix[0][0] = -1.7362543;
  matrix2.matrix[0][1] = 2.7740213;
  matrix2.matrix[1][0] = 2.9751503;
  matrix2.matrix[1][1] = -0.6493745;
  matrix_t expected = {0};
  create_matrix(2, 2, &expected);
  expected.matrix[0][0] = -6.96879115351534;
  expected.matrix[0][1] = 2.67076015961202;
  expected.matrix[1][0] = 1.77767842683431;
  expected.matrix[1][1] = 6.19767729837531;
  // matrix1.matrix_type = CORRECT_MATRIX;
  // matrix2.matrix_type = CORRECT_MATRIX;
  // expected.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_matrix(&matrix1, &matrix2, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_mult_matrix_5) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t matrix2 = {0};
  create_matrix(3, 3, &matrix2);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] =
          (matrix2.rows * matrix2.columns) - (i * matrix2.columns + j);
    }
  }
  // matrix2.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  mult_matrix(&matrix1, &matrix2, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&matrix2);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_transpose_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 7;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 6;
  expected.matrix[2][2] = 9;
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  transpose(&matrix1, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_transpose_2) {
  matrix_t matrix1 = {0};
  create_matrix(3, 1, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t expected = {0};
  create_matrix(1, 3, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  transpose(&matrix1, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_transpose_3) {
  matrix_t matrix1 = {0};
  create_matrix(2, 2, &matrix1);
  matrix1.matrix[0][0] = 0.5529605;
  matrix1.matrix[0][1] = -0.3930814;
  matrix1.matrix[1][0] = -0.5199081;
  matrix1.matrix[1][1] = -2.0958774;
  matrix_t expected = {0};
  create_matrix(2, 2, &expected);
  expected.matrix[0][0] = 0.5529605;
  expected.matrix[0][1] = -0.5199081;
  expected.matrix[1][0] = -0.3930814;
  expected.matrix[1][1] = -2.0958774;
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  transpose(&matrix1, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_transpose_4) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t result = {0};
  transpose(&matrix1, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_calc_complements_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  expected.matrix[0][0] = -3;
  expected.matrix[0][1] = 6;
  expected.matrix[0][2] = -3;
  expected.matrix[1][0] = 6;
  expected.matrix[1][1] = -12;
  expected.matrix[1][2] = 6;
  expected.matrix[2][0] = -3;
  expected.matrix[2][1] = 6;
  expected.matrix[2][2] = -3;
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  calc_complements(&matrix1, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_calc_complements_2) {
  matrix_t matrix1 = {0};
  create_matrix(2, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  calc_complements(&matrix1, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_calc_complements_3) {
  matrix_t matrix1 = {0};
  create_matrix(1, 1, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 6;
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  calc_complements(&matrix1, &result);
  // fail_if(!(result.matrix_type != INCORRECT_MATRIX));
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_calc_complements_4) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t result = {0};
  calc_complements(&matrix1, &result);
  // fail_if(result.matrix_type != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_calc_complements_5) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 0.5885548;
  matrix1.matrix[0][1] = -2.1592210;
  matrix1.matrix[0][2] = -2.0269028;
  matrix1.matrix[1][0] = 1.8449226;
  matrix1.matrix[1][1] = -0.3857403;
  matrix1.matrix[1][2] = 2.8620989;
  matrix1.matrix[2][0] = 1.2957987;
  matrix1.matrix[2][1] = -1.5112104;
  matrix1.matrix[2][2] = -0.9130192;
  matrix_t expected = {0};
  create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 4.6774219;
  expected.matrix[0][1] = 5.3931538;
  expected.matrix[0][2] = -2.2882244;
  expected.matrix[1][0] = 1.0916663;
  expected.matrix[1][1] = 2.0890961;
  expected.matrix[1][2] = -1.9084856;
  expected.matrix[2][0] = -6.9617621;
  expected.matrix[2][1] = -5.4239808;
  expected.matrix[2][2] = 3.7565663;
  // expected.matrix_type = CORRECT_MATRIX;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  calc_complements(&matrix1, &result);
  fail_if(!(eq_matrix(&result, &expected)));
  remove_matrix(&matrix1);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_determinant_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  double expected = 0.0;
  double result = 0;
  determinant(&matrix1, &result);
  fail_if(result != expected);
  remove_matrix(&matrix1);
}
END_TEST

START_TEST(test4_determinant_3) {
  matrix_t matrix1 = {0};
  create_matrix(1, 1, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  double expected = matrix1.matrix[0][0];
  double result;
  determinant(&matrix1, &result);
  fail_if(result != expected);
  remove_matrix(&matrix1);
}
END_TEST

START_TEST(test4_determinant_5) {
  matrix_t s = {0};
  create_matrix(4, 4, &s);
  s.matrix[0][0] = 1;
  s.matrix[0][1] = 1;
  s.matrix[0][2] = 3;
  s.matrix[0][3] = 3;
  s.matrix[1][0] = 1;
  s.matrix[1][1] = 0;
  s.matrix[1][2] = 9;
  s.matrix[1][3] = 8;
  s.matrix[2][0] = 2;
  s.matrix[2][1] = 0;
  s.matrix[2][2] = 7;
  s.matrix[2][3] = 1;
  s.matrix[3][0] = 4;
  s.matrix[3][1] = 0;
  s.matrix[3][2] = 2;
  s.matrix[3][3] = 1;
  double result = 0;
  determinant(&s, &result);
  fail_if(!(result == 169));
  remove_matrix(&s);
}
END_TEST

START_TEST(test4_determinant_6) {
  matrix_t s = {0};
  create_matrix(4, 4, &s);
  s.matrix[0][0] = 1;
  s.matrix[0][1] = 0;
  s.matrix[0][2] = 3;
  s.matrix[0][3] = 3;
  s.matrix[1][0] = 1;
  s.matrix[1][1] = 0;
  s.matrix[1][2] = 9;
  s.matrix[1][3] = 8;
  s.matrix[2][0] = 2;
  s.matrix[2][1] = 0;
  s.matrix[2][2] = 7;
  s.matrix[2][3] = 1;
  s.matrix[3][0] = 4;
  s.matrix[3][1] = 0;
  s.matrix[3][2] = 2;
  s.matrix[3][3] = 1;
  double result = 0;
  determinant(&s, &result);
  ck_assert_int_eq(result, 0);
  remove_matrix(&s);
}
END_TEST

START_TEST(test4_determinant_7) {
  matrix_t s = {0};
  double result = 0;
  create_matrix(4, 4, &s);
  s.matrix[0][0] = 1;
  s.matrix[0][1] = 0;
  s.matrix[0][2] = NAN;
  s.matrix[0][3] = 3;
  s.matrix[1][0] = 1;
  s.matrix[1][1] = 0;
  s.matrix[1][2] = 9;
  s.matrix[1][3] = 8;
  s.matrix[2][0] = 2;
  s.matrix[2][1] = 0;
  s.matrix[2][2] = 7;
  s.matrix[2][3] = 1;
  s.matrix[3][0] = 4;
  s.matrix[3][1] = 0;
  s.matrix[3][2] = 2;
  s.matrix[3][3] = 1;

  determinant(&s, &result);
  fail_if(!(result != result));
  remove_matrix(&s);
}
END_TEST

START_TEST(test4_inverse_matrix_1) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  matrix_t result = {0};
  int r = inverse_matrix(&matrix1, &result);
  fail_if(r != CALCULATION_ERROR);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_inverse_matrix_2) {
  matrix_t matrix1 = {0};
  create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 0.6548129;
  matrix1.matrix[0][1] = 1.4396934;
  matrix1.matrix[0][2] = -1.0722451;
  matrix1.matrix[1][0] = 2.7769395;
  matrix1.matrix[1][1] = -1.9783084;
  matrix1.matrix[1][2] = 2.5705703;
  matrix1.matrix[2][0] = -2.4244804;
  matrix1.matrix[2][1] = -2.2425174;
  matrix1.matrix[2][2] = -2.0103526;
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  inverse_matrix(&matrix1, &result);
  matrix_t checker = {0};
  mult_matrix(&result, &matrix1, &checker);
  // ck_assert_int_eq(checker.matrix[0][0], 1);
  ck_assert(fabsl(checker.matrix[0][0] - 1) < ACC);
  ck_assert(fabsl(checker.matrix[1][1] - 1) < ACC);
  ck_assert(fabsl(checker.matrix[2][2] - 1) < ACC);
  // ck_assert_int_eq(checker.matrix[2][2], 1);
  remove_matrix(&matrix1);
  remove_matrix(&result);
  remove_matrix(&checker);
}
END_TEST

START_TEST(test4_inverse_matrix_3) {
  matrix_t matrix1 = {0};
  create_matrix(1, 6, &matrix1);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = i * matrix1.columns + j + 1;
    }
  }
  // matrix1.matrix_type = CORRECT_MATRIX;
  matrix_t result = {0};
  int r = inverse_matrix(&matrix1, &result);
  fail_if(r != CALCULATION_ERROR);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test4_inverse_matrix_4) {
  matrix_t matrix1 = {0};
  create_matrix(0, 0, &matrix1);
  matrix_t result = {0};
  int r = inverse_matrix(&matrix1, &result);
  fail_if(r != INCORRECT_MATRIX);
  remove_matrix(&matrix1);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_NULL_eq) { ck_assert(FAILURE == eq_matrix(NULL, NULL)); }
END_TEST

START_TEST(test_NULL_sub) {
  ck_assert(INCORRECT_MATRIX == sub_matrix(NULL, NULL, NULL));
}
END_TEST

START_TEST(test_NULL_sum) {
  ck_assert(INCORRECT_MATRIX == sum_matrix(NULL, NULL, NULL));
}
END_TEST

START_TEST(test_NULL_mult_num) {
  ck_assert(INCORRECT_MATRIX == mult_number(NULL, 0.0, NULL));
}
END_TEST

START_TEST(test_NULL_mult_matrix) {
  ck_assert(INCORRECT_MATRIX == mult_matrix(NULL, NULL, NULL));
}
END_TEST

START_TEST(test_NULL_transpose) {
  ck_assert(INCORRECT_MATRIX == transpose(NULL, NULL));
}
END_TEST

START_TEST(test_NULL_det) {
  ck_assert(INCORRECT_MATRIX == determinant(NULL, NULL));
}
END_TEST

START_TEST(test_NULL_complements) {
  ck_assert(INCORRECT_MATRIX == calc_complements(NULL, NULL));
}
END_TEST

START_TEST(test_NULL_inverse) {
  ck_assert(INCORRECT_MATRIX == inverse_matrix(NULL, NULL));
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, eq_matrix_test_1);
  tcase_add_test(tc1_1, eq_matrix_test_2);
  tcase_add_test(tc1_1, eq_matrix_test_3);
  tcase_add_test(tc1_1, eq_matrix_test_4);
  tcase_add_test(tc1_1, sum_matrix_test_1);
  tcase_add_test(tc1_1, sum_matrix_test_2);
  tcase_add_test(tc1_1, sum_matrix_test_3);
  tcase_add_test(tc1_1, sub_matrix_test_1);
  tcase_add_test(tc1_1, sub_matrix_test_2);
  tcase_add_test(tc1_1, mult_number_test_1);
  tcase_add_test(tc1_1, mult_number_test_2);
  tcase_add_test(tc1_1, mult_matrix_test_1);
  tcase_add_test(tc1_1, mult_matrix_test_2);
  tcase_add_test(tc1_1, transpose_test_1);
  tcase_add_test(tc1_1, transpose_test_2);
  tcase_add_test(tc1_1, calc_complements_test_1);
  tcase_add_test(tc1_1, calc_complements_test_2);
  tcase_add_test(tc1_1, determinant_test_1);
  tcase_add_test(tc1_1, determinant_test_2);
  tcase_add_test(tc1_1, inverse_matrix_test_1);
  tcase_add_test(tc1_1, inverse_matrix_test_2);
  tcase_add_test(tc1_1, create_matrix_test_1);
  tcase_add_test(tc1_1, valid_matrix_test_1);
  tcase_add_test(tc1_1, inverse_matrix_test_3);
  tcase_add_test(tc1_1, inverse_matrix_test_4);
  tcase_add_test(tc1_1, test2_create_matrix);
  tcase_add_test(tc1_1, test2_eq_matrix);
  tcase_add_test(tc1_1, test2_sum_matrix);
  tcase_add_test(tc1_1, test2_sub_matrix);
  tcase_add_test(tc1_1, test2_mult_number);
  tcase_add_test(tc1_1, test2_mult_matrix);
  tcase_add_test(tc1_1, test2_transpose);
  tcase_add_test(tc1_1, test2_calc_complements);
  tcase_add_test(tc1_1, test2_determinant);
  tcase_add_test(tc1_1, test2_determinant_2);
  tcase_add_test(tc1_1, test2_determinant_3);
  tcase_add_test(tc1_1, test2_inverse_matrix);
  tcase_add_test(tc1_1, test3_create_matrix);
  tcase_add_test(tc1_1, test3_eq_matrix);
  tcase_add_test(tc1_1, test3_sum_matrix);
  tcase_add_test(tc1_1, test3_sub_matrix);
  tcase_add_test(tc1_1, test3_mult_number);
  tcase_add_test(tc1_1, test3_mult_matrix);
  tcase_add_test(tc1_1, test3_transpose);
  tcase_add_test(tc1_1, test3_determinant);
  tcase_add_test(tc1_1, test3_calc_complements);
  tcase_add_test(tc1_1, test3_inverse_matrix);
  tcase_add_test(tc1_1, test4_create_1);
  tcase_add_test(tc1_1, test4_create_2);
  tcase_add_test(tc1_1, test4_create_3);
  tcase_add_test(tc1_1, test4_rem_1);
  tcase_add_test(tc1_1, test4_eq_1);
  tcase_add_test(tc1_1, test4_eq_2);
  tcase_add_test(tc1_1, test4_sum_2);
  tcase_add_test(tc1_1, test4_sub_1);
  tcase_add_test(tc1_1, test4_sub_2);
  tcase_add_test(tc1_1, test4_sub_3);
  tcase_add_test(tc1_1, test4_mult_num_1);
  tcase_add_test(tc1_1, test4_mult_num_2);
  tcase_add_test(tc1_1, test4_mult_m_1);
  tcase_add_test(tc1_1, test4_mult_m_2);
  tcase_add_test(tc1_1, test4_trans_1);
  tcase_add_test(tc1_1, test4_trans_2);
  tcase_add_test(tc1_1, test4_calc_compl_1);
  tcase_add_test(tc1_1, test4_calc_compl_2);
  tcase_add_test(tc1_1, test4_determ_1);
  tcase_add_test(tc1_1, test4_inverse_1);
  tcase_add_test(tc1_1, test4_inverse_2);
  tcase_add_test(tc1_1, test4_inverse_3);
  tcase_add_test(tc1_1, test4_eq_matrix_1);
  tcase_add_test(tc1_1, test4_eq_matrix_2);
  tcase_add_test(tc1_1, test4_eq_matrix_3);
  tcase_add_test(tc1_1, test4_sum_matrix_1);
  tcase_add_test(tc1_1, test4_sum_matrix_2);
  tcase_add_test(tc1_1, test4_sum_matrix_4);
  tcase_add_test(tc1_1, test4_sum_matrix_5);
  tcase_add_test(tc1_1, test4_sum_matrix_6);
  tcase_add_test(tc1_1, test4_sub_matrix_1);
  tcase_add_test(tc1_1, test4_sub_matrix_2);
  tcase_add_test(tc1_1, test4_sub_matrix_4);
  tcase_add_test(tc1_1, test4_sub_matrix_5);
  tcase_add_test(tc1_1, test4_mult_number_1);
  tcase_add_test(tc1_1, test4_mult_number_2);
  tcase_add_test(tc1_1, test4_mult_number_3);
  tcase_add_test(tc1_1, test4_mult_number_4);
  tcase_add_test(tc1_1, test4_mult_matrix_1);
  tcase_add_test(tc1_1, test4_mult_matrix_2);
  tcase_add_test(tc1_1, test4_mult_matrix_3);
  tcase_add_test(tc1_1, test4_mult_matrix_4);
  tcase_add_test(tc1_1, test4_mult_matrix_5);
  tcase_add_test(tc1_1, test4_transpose_1);
  tcase_add_test(tc1_1, test4_transpose_2);
  tcase_add_test(tc1_1, test4_transpose_3);
  tcase_add_test(tc1_1, test4_transpose_4);
  tcase_add_test(tc1_1, test4_calc_complements_1);
  tcase_add_test(tc1_1, test4_calc_complements_2);
  tcase_add_test(tc1_1, test4_calc_complements_3);
  tcase_add_test(tc1_1, test4_calc_complements_4);
  tcase_add_test(tc1_1, test4_calc_complements_5);
  tcase_add_test(tc1_1, test4_determinant_1);
  tcase_add_test(tc1_1, test4_determinant_3);
  tcase_add_test(tc1_1, test4_determinant_5);
  tcase_add_test(tc1_1, test4_determinant_6);
  tcase_add_test(tc1_1, test4_determinant_7);
  tcase_add_test(tc1_1, test4_inverse_matrix_1);
  tcase_add_test(tc1_1, test4_inverse_matrix_2);
  tcase_add_test(tc1_1, test4_inverse_matrix_3);
  tcase_add_test(tc1_1, test4_inverse_matrix_4);
  tcase_add_test(tc1_1, test_NULL_eq);
  tcase_add_test(tc1_1, test_NULL_sub);
  tcase_add_test(tc1_1, test_NULL_sum);
  tcase_add_test(tc1_1, test_NULL_mult_num);
  tcase_add_test(tc1_1, test_NULL_mult_matrix);
  tcase_add_test(tc1_1, test_NULL_transpose);
  tcase_add_test(tc1_1, test_NULL_det);
  tcase_add_test(tc1_1, test_NULL_complements);
  tcase_add_test(tc1_1, test_NULL_inverse);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
