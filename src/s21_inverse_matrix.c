#include "s21_matrix.h"

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
	int error = CORRECT;
	if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    		error = INCORRECT_MATRIX;
	}
	if(error == CORRECT) {
		double determinant = 0.0;
		error = s21_determinant(A, &determinant);
		if(error != CORRECT || determinant == 0.0 || A->rows != A->columns) {
			error = CALCULATION_ERROR;
		} else if(A->rows == 1) {
			error = s21_create_matrix(A->rows, A->columns, result);
			if(error == CORRECT) {
				result->matrix[0][0] = 1 / A->matrix[0][0];
			}
		} else if(error == CORRECT) {
			matrix_t calc_complements;
			matrix_t transpose;
			error = s21_calc_complements(A, &calc_complements);
			if(error == CORRECT) {
				error = s21_transpose(&calc_complements, &transpose);
			}
			if(error == CORRECT) {
				error = s21_mult_number(&transpose, 1/determinant, result);
			}
			s21_remove_matrix(&transpose);
			s21_remove_matrix(&calc_complements);
		}
	}
	return error;
}
