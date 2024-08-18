#include "s21_matrix.h"

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = CORRECT;
  if (!correct_structure(A) || !correct_structure(B) || result == NULL)
    error = INCORRECT_MATRIX;
  else if (!equal_size_of_the_matrices(A, B) || !correct_matrix(A) ||
           !correct_matrix(B))
    error = CALCULATION_ERROR;
  else {
    error = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows && error == CORRECT; i++)
      for (int j = 0; j < result->columns && error == CORRECT; j++) {
        double a = A->matrix[i][j];
        double b = B->matrix[i][j];
        result->matrix[i][j] = a + b;
        if (isnan(a + b) || isinf(a + b)) {
          error = CALCULATION_ERROR;
          s21_remove_matrix(result);
        }
      }
  }
  return error;
}
