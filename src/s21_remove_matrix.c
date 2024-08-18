#include "s21_matrix.h"

// Очистка матрицы
void s21_remove_matrix(matrix_t *A) {
  if (correct_structure(A)) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
  }
  if (A != NULL) {
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}
