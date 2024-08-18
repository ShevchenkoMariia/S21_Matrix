#include "testing.h"

// Тесты для функции s21_eq_matrix

// Блок тестов, в результате которых должна быть ошибка
START_TEST(tests_error_calc_1) {
  matrix_t matrix_a, matrix_b;
  for (int i = 0; i < 10; i++) {
    generating_two_different_matrices(&matrix_a, &matrix_b);

    int res = s21_eq_matrix(&matrix_a, &matrix_b);

    ck_assert_int_eq(res, FAILURE);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }
}
END_TEST

START_TEST(tests_error_calc_2) {
  double invalid_numbers[3] = {INFINITY, -INFINITY, NAN};
  matrix_t matrix_a, matrix_b;

  for (int i = 0; i < 3; i++) {
    generating_two_identical_matrices(&matrix_a, &matrix_b);

    matrix_b.matrix[0][0] = invalid_numbers[i];

    int res = s21_eq_matrix(&matrix_a, &matrix_b);

    ck_assert_int_eq(res, FAILURE);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }
}
END_TEST

START_TEST(test_error_3) {
  matrix_t matrix_a, matrix_b;

  generating_two_identical_matrices(&matrix_a, &matrix_b);

  matrix_b.matrix[0][0] += 1.0;

  int res = s21_eq_matrix(&matrix_a, &matrix_b);

  ck_assert_int_eq(res, FAILURE);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);
}
END_TEST

START_TEST(test_error_4) {
  matrix_t matrix_a, matrix_b;
  generating_two_identical_matrices(&matrix_a, &matrix_b);

  matrix_a.matrix[0][0] += 0.000002;

  int res = s21_eq_matrix(&matrix_a, &matrix_b);

  ck_assert_int_eq(res, FAILURE);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);
}
END_TEST

START_TEST(test_error_5) {
  matrix_t matrix_a, matrix_b;

  generating_two_identical_matrices(&matrix_a, &matrix_b);

  matrix_a.matrix[0][0] += 0.0000079;

  int res = s21_eq_matrix(&matrix_a, &matrix_b);

  ck_assert_int_eq(res, FAILURE);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);
}
END_TEST

START_TEST(test_error_6) {
  matrix_t *matrix_a = NULL;
  matrix_t matrix_b;

  s21_create_matrix(3, 5, &matrix_b);

  int res = s21_eq_matrix(matrix_a, &matrix_b);

  ck_assert_int_eq(res, FAILURE);

  s21_remove_matrix(&matrix_b);
}
END_TEST

//Блок тестов без ошибок
START_TEST(random_correct_tests) {
  matrix_t matrix_a, matrix_b;

  for (int a = 0; a < 10; a++) {
    generating_two_identical_matrices(&matrix_a, &matrix_b);

    int res = s21_eq_matrix(&matrix_a, &matrix_b);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);

    ck_assert_int_eq(res, SUCCESS);
  }
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  // success with uninitialized values
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  // success with a difference of less than 1e-7
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  A.matrix[0][0] = 0.000000001;
  A.matrix[0][0] = 0.000000002;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  // failure with different dimensions of matrices
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(3, 4, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  // failure with INCORRECT_MATRIX
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

// Создание набора тестов
Suite *test_s21_eq_matrix(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc = tcase_create("s21_eq_matrix");

  tcase_add_test(tc, tests_error_calc_1);
  tcase_add_test(tc, tests_error_calc_2);
  tcase_add_test(tc, test_error_3);
  tcase_add_test(tc, test_error_4);
  tcase_add_test(tc, test_error_5);
  tcase_add_test(tc, test_error_6);

  tcase_add_test(tc, random_correct_tests);
  tcase_add_test(tc, s21_eq_matrix_2);
  tcase_add_test(tc, s21_eq_matrix_3);
  tcase_add_test(tc, s21_eq_matrix_4);
  tcase_add_test(tc, s21_eq_matrix_5);

  suite_add_tcase(s, tc);
  return s;
}
