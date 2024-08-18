#include "s21_matrix.h"

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = CORRECT;
  if (!correct_structure(A) || result == NULL)
    error = INCORRECT_MATRIX;
  else if (!correct_matrix(A) || A->rows != A->columns)
    error = CALCULATION_ERROR;
  else {
    error = s21_create_matrix(A->rows, A->columns, result);
    matrix_t submatrix;
    for (int i = 0; i < result->rows && error == CORRECT; i++) {
      for (int j = 0; j < result->columns && error == CORRECT; j++) {
        s21_create_matrix(A->rows - 1, A->columns - 1, &submatrix);
        error = finding_a_minor_for_a_matrix(A, i, j, &submatrix);
        double determinant = 0.0;
        error = s21_determinant(&submatrix, &determinant);
        s21_remove_matrix(&submatrix);
        if ((i + j) % 2 != 0) determinant *= -1;
        result->matrix[i][j] = determinant;
        if (error != CORRECT || isinf(determinant) || isnan(determinant)) {
          s21_remove_matrix(result);
          error = CALCULATION_ERROR;
        }
      }
    }
  }
  return error;
}
