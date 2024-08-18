#include "s21_matrix.h"

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = CORRECT;
  if (!correct_structure(A) || result == NULL)
    error = INCORRECT_MATRIX;
  else if (!correct_matrix(A))
    error = CALCULATION_ERROR;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[j][i];
  }
  return error;
}
