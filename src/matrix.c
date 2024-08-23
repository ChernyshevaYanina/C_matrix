#include "matrix.h"

static int equal_matrix_size(matrix_t *A, matrix_t *B) {
  int result = CALC_ERROR;
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    result = OK;
  }
  return result;
}

static int is_square(matrix_t *A) {
  int result = CALC_ERROR;
  if (A->rows == A->columns) {
    result = OK;
  }
  return result;
}

static int equal_rows_and_columns(matrix_t *A, matrix_t *B) {
  int result = CALC_ERROR;
  if (A->columns == B->rows) {
    result = OK;
  }
  return result;
}

static int is_positiv(int rows, int columns) {
  int status = INCORRECT_MATRIX;
  if (rows > 0 && columns > 0) {
    status = OK;
  }
  return status;
}

int create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  status = is_positiv(rows, columns);
  if (status == OK && result) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }

  return status;
}

void remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A == NULL || B == NULL) {
    result = FAILURE;
  } else {
    int equalSize = equal_matrix_size(A, B);
    if (equalSize == OK) {
      int loop_break = 0;
      for (int i = 0; i < A->rows && loop_break == 0; i++) {
        for (int j = 0; j < A->columns && loop_break == 0; j++)
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS_EQ) {
            result = FAILURE;
            loop_break = 1;
          }
      }
    } else {
      result = FAILURE;
    }
  }
  return result;
}

static int sum_and_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result,
                                  double sign) {
  int status = OK;
  if (A == NULL || B == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    if (is_positiv(A->rows, A->columns) == OK &&
        is_positiv(B->rows, B->columns) == OK) {
      status = equal_matrix_size(A, B);
      if (status == OK) {
        status = create_matrix(A->rows, A->columns, result);
        if (status == OK) {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              result->matrix[i][j] =
                  (A->matrix[i][j] + (B->matrix[i][j] * sign));
            }
          }
        }
      }
    } else {
      status = INCORRECT_MATRIX;
    }
  }
  return status;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_and_sub_matrix(A, B, result, 1.);
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_and_sub_matrix(A, B, result, -1.);
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  if (A == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    status = is_positiv(A->rows, A->columns);
    if (status == OK) {
      int row = A->rows, column = A->columns;
      status = create_matrix(row, column, result);
      if (status == OK) {
        for (int i = 0; i < row; i++) {
          for (int j = 0; j < column; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
          }
        }
      }
    }
  }
  return status;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (A == NULL || B == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    if (is_positiv(A->rows, A->columns) == OK &&
        is_positiv(B->rows, B->columns) == OK) {
      status = equal_rows_and_columns(A, B);
      if (status == OK) {
        status = create_matrix(A->rows, B->columns, result);
        if (status == OK) {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
              for (int k = 0; k < B->rows; k++) {
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
              }
            }
          }
        }
      }
    } else {
      status = INCORRECT_MATRIX;
    }
  }
  return status;
}

int transpose(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    status = create_matrix(A->columns, A->rows, result);
    if (status == OK) {
      for (int j = 0; j < A->rows; j++) {
        for (int i = 0; i < A->columns; i++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return status;
}

int matrix_minor(matrix_t *A, matrix_t *result, int row, int column) {
  int status = is_positiv(A->rows, A->columns);
  if (status == OK) {
    status = is_square(A);
    if (status == OK) {
      int rowA = A->rows - 1, columnA = A->columns - 1;
      status = create_matrix(rowA, columnA, result);
      if (status == OK) {
        int c = 0;
        for (int i = 0; i < A->rows; i++) {
          if (i == row) {
            continue;
          } else {
            int k = 0;
            for (int j = 0; j < A->columns; j++) {
              if (j == column) {
                continue;
              } else {
                result->matrix[c][k] = A->matrix[i][j];
                k++;
              }
            }
            c++;
          }
        }
      }
    }
  }
  return status;
}

int determinant(matrix_t *A, double *result) {
  int status = OK;
  if (A == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    status = is_positiv(A->rows, A->columns);
    if (status == OK) {
      (*result) = 0.0;
      status = is_square(A);
      if (status == OK) {
        if (A->rows == 1) {
          *result = A->matrix[0][0];
        } else if (A->columns == 2) {
          *result = A->matrix[0][0] * A->matrix[1][1] -
                    A->matrix[1][0] * A->matrix[0][1];
        } else {
          int columns = A->columns;
          double determinant_value = 0;
          matrix_t temp;
          int sign = 1;
          for (int i = 0; i < columns; i++) {
            matrix_minor(A, &temp, 0, i);
            // determinant = 0.0;
            determinant(&temp, &determinant_value);
            remove_matrix(&temp);
            *result += A->matrix[0][i] * determinant_value * sign;
            sign = -sign;
          }
        }
      }
    }
  }
  return status;
}

int calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    status = is_positiv(A->rows, A->columns);
    if (status == OK) {
      status = is_square(A);
      if (status == OK) {
        double minor = 0;
        int column = A->columns, row = A->rows;
        status = create_matrix(row, column, result);
        if (A->rows == 1) {
          result->matrix[0][0] = pow(A->matrix[0][0], 2);
        } else {
          for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
              matrix_t temp = {0};
              matrix_minor(A, &temp, i, j);
              determinant(&temp, &minor);
              result->matrix[i][j] = (minor * pow(-1, (i + j)));
              remove_matrix(&temp);
            }
          }
        }
      }
    }
  }
  return status;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    status = is_positiv(A->rows, A->columns);
    if (status == OK) {
      status = is_square(A);
        if (status == OK) {
          matrix_t temp;
          double determinant_value = 0;
          determinant(A, &determinant_value);
          if (determinant_value != 0) {
            calc_complements(A, result);
            transpose(result, &temp);
            remove_matrix(result);
            mult_number(&temp, (1 / determinant_value), result);
            remove_matrix(&temp);
          } else {
            status = CALC_ERROR;
          }
        }
      }
    }
  return status;
}
