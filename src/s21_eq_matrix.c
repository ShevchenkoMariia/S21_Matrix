#include "s21_matrix.h"

/*
 * Сравнение матриц
 * Сравнение должно происходить до шестого знака после запятой
 * включительно Если матрицы равны, возвращаем SUCCESS, если нет - FAILURE
 */

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int comparison = SUCCESS;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      !equal_size_of_the_matrices(A, B))
    comparison = FAILURE;
  else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > ACCURACY ||
            isinf(A->matrix[i][j]) || isinf(B->matrix[i][j]) ||
            isnan(A->matrix[i][j]) || isnan(B->matrix[i][j])) {
          comparison = FAILURE;
          break;
        }
      }
  }
  return comparison;
}
