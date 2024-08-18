#include "s21_matrix.h"

// Умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = CORRECT;
  if (!correct_structure(A) || !correct_structure(B) || result == NULL)
    error = INCORRECT_MATRIX;
  else if ((A->rows != B->columns) || !correct_matrix(A) || !correct_matrix(B))
    error = CALCULATION_ERROR;
  else {
    error = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows && error == CORRECT; i++)
      for (int j = 0; j < result->columns && error == CORRECT; j++) {
        for (int a = 0; a < A->columns && error == CORRECT; a++) {
          result->matrix[i][j] += A->matrix[i][a] * B->matrix[a][j];
          if (isinf(result->matrix[i][j]) || isnan(result->matrix[i][j])) {
            error = CALCULATION_ERROR;
            s21_remove_matrix(result);
          }
        }
      }
  }
  return error;
}
