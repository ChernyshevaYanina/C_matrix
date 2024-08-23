#ifndef MATRIX_H
#define MATRIX_H

#define SUCCESS 1
#define FAILURE 0
#define EPS_EQ 1e-7

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2 } ReturnValues;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int calc_complements(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int inverse_matrix(matrix_t *A, matrix_t *result);

// --------------MY FUNCS--------------

static int equal_matrix_size(matrix_t *A, matrix_t *B);
static int is_square(matrix_t *A);
static int equal_rows_and_columns(matrix_t *A, matrix_t *B);
static int is_positiv(int rows, int columns);
static int sum_and_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result,
                                  double sign);
int matrix_minor(matrix_t *A, matrix_t *result, int row, int column);

#endif  // MATRIX_H
