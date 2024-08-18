#ifndef TESTING_H
#define TESTING_H

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

// Функции с наборами тестов
Suite *test_s21_create_matrix();
Suite *test_s21_remove_matrix();
Suite *test_s21_eq_matrix();
Suite *test_s21_sum_matrix();
Suite *test_s21_sub_matrix();
Suite *test_s21_mult_matrix();
Suite *test_s21_mult_number();
Suite *test_s21_calc_complements();
Suite *test_s21_determinant();
Suite *test_s21_transpose();
Suite *test_s21_inverse_matrix();

// Генерация рандомной матрицы
void random_matrix_generation(matrix_t *matrix);

// Генерация двух разных рандомных матриц
void generating_two_different_matrices(matrix_t *matrix_A, matrix_t *matrix_B);

// Генерация двух идентичных матриц
void generating_two_identical_matrices(matrix_t *matrix_A, matrix_t *matrix_B);

// Генерация двух одинаковых по размеру матриц, но разных по наполнению
void generating_two_matrices_of_the_same_size(matrix_t *matrix_A,
                                              matrix_t *matrix_B);

// Генерация двух матриц, где A->rows == B->columns
void generating_two_matrices_for_mult(matrix_t *matrix_A, matrix_t *matrix_B);

// Генерация квадратной матрицы
void generating_a_square_matrix(matrix_t *A);

#endif
