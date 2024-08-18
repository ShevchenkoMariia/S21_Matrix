#include "testing.h"

// Тесты для функции s21_inverse_matrix

// Блок тестов с ошибкой
START_TEST(test_error_1) {
  matrix_t *A = NULL;
  matrix_t result;
  int res = s21_inverse_matrix(A, &result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_2) {
  matrix_t A;
  matrix_t *result = NULL;

  s21_create_matrix(2, 1, &A);

  int res = s21_inverse_matrix(&A, result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_error_3) {
  matrix_t A, result;
  A.matrix = NULL;
  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_4) {
  matrix_t A, result;
  double invalid_number[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    generating_a_square_matrix(&A);
    A.matrix[0][0] = invalid_number[i];

    int res = s21_inverse_matrix(&A, &result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(test_error_5) {
  matrix_t A, result;

  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 4.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = -3.0;
  A.matrix[1][0] = -8.0;
  A.matrix[1][1] = -7.0;
  A.matrix[1][2] = 1.0;
  A.matrix[2][0] = 4.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = -3.0;

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_error_6) {
  matrix_t A, result;

  random_matrix_generation(&A);

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

// Блок тестов без ошибок
START_TEST(correct_test_1) {
  matrix_t A, result;

  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], -1.0);
  ck_assert_double_eq(result.matrix[0][2], 1.0);
  ck_assert_double_eq(result.matrix[1][0], -38.0);
  ck_assert_double_eq(result.matrix[1][1], 41.0);
  ck_assert_double_eq(result.matrix[1][2], -34.0);
  ck_assert_double_eq(result.matrix[2][0], 27.0);
  ck_assert_double_eq(result.matrix[2][1], -29.0);
  ck_assert_double_eq(result.matrix[2][2], 24.0);

  ck_assert_int_eq(res, CORRECT);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  // failure when matrix has determinant equal to zero
  matrix_t A;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  // failure with non-square matrix
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 3, &A);
  A.matrix[0][0] = 0.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_4) {
  // success matrix 1x1
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &eq_matrix);
  A.matrix[0][0] = 21;
  eq_matrix.matrix[0][0] = 1.0 / 21.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CORRECT);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_5) {
  // success with task reference values
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;
  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = -1,
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = -38, eq_matrix.matrix[1][1] = 41,
  eq_matrix.matrix[1][2] = -34;
  eq_matrix.matrix[2][0] = 27, eq_matrix.matrix[2][1] = -29,
  eq_matrix.matrix[2][2] = 24;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CORRECT);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_6) {
  matrix_t A;
  matrix_t result;
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Создание набора тестов
Suite *test_s21_inverse_matrix(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("s21_inverse_matrix");

  tcase_add_test(tc, test_error_1);
  tcase_add_test(tc, test_error_2);
  tcase_add_test(tc, test_error_3);
  tcase_add_test(tc, test_error_4);
  tcase_add_test(tc, test_error_5);
  tcase_add_test(tc, test_error_6);

  tcase_add_test(tc, s21_inverse_matrix_2);
  tcase_add_test(tc, s21_inverse_matrix_3);
  tcase_add_test(tc, s21_inverse_matrix_4);
  tcase_add_test(tc, s21_inverse_matrix_5);
  tcase_add_test(tc, s21_inverse_matrix_6);
  tcase_add_test(tc, correct_test_1);

  suite_add_tcase(s, tc);
  return s;
}
