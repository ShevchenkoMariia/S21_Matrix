#include "s21_matrix.h"

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = CORRECT;
  if (!correct_structure(A) || !correct_structure(B) || result == NULL)
    error = INCORRECT_MATRIX;
  else if (!equal_size_of_the_matrices(A, B) || !correct_matrix(A) ||
           !correct_matrix(B))
    error = CALCULATION_ERROR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++) {
        double a = A->matrix[i][j];
        double b = B->matrix[i][j];
        result->matrix[i][j] = a - b;
      }
  }
  return error;
}
