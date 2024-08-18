#include "s21_matrix.h"

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  int error = CORRECT;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALCULATION_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else if (A->rows > 2) {
    int row_for_deletion = 0;
    *result = 0.0;
    for (int i = 0; i < A->columns && error == CORRECT; i++) {
      if (isnan(A->matrix[0][i]) || isinf(A->matrix[0][i])) {
        error = CALCULATION_ERROR;
        break;
      }
      matrix_t submatrix;
      s21_create_matrix(A->rows - 1, A->columns - 1, &submatrix);
      error = finding_a_minor_for_a_matrix(A, row_for_deletion, i, &submatrix);
      if (error == CORRECT) {
        double determinant = 0.0;
        error = s21_determinant(&submatrix, &determinant);
        if (error == CORRECT) {
          if (i % 2 != 0) {
            determinant *= -1.0;
          }
          *result += A->matrix[0][i] * determinant;
          if (isnan(*result) || isinf(*result)) {
            error = CALCULATION_ERROR;
          }
        }
        s21_remove_matrix(&submatrix);
      }
    }
  }
  return error;
}
