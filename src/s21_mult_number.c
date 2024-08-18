#include "s21_matrix.h"

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = CORRECT;
  if (!correct_structure(A) || result == NULL)
    error = INCORRECT_MATRIX;
  else if (isnan(number) || isinf(number) || !correct_matrix(A))
    error = CALCULATION_ERROR;
  else {
    error = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows && error != CALCULATION_ERROR; i++)
      for (int j = 0; j < result->columns && error != CALCULATION_ERROR; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (isnan(result->matrix[i][j]) || isinf(result->matrix[i][j])) {
          error = CALCULATION_ERROR;
          s21_remove_matrix(result);
          break;
        }
      }
  }
  return error;
}
