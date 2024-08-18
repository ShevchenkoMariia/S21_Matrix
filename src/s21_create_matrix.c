#include "s21_matrix.h"

// Создание матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = CORRECT;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    error = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix == NULL) error = INCORRECT_MATRIX;
  }
  return error;
}
