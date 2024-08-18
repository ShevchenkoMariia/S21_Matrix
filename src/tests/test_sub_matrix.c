#include "testing.h"

// Тесты для функции s21_sub_matrix

// Блок тестов, в результате которых должна быть ошибка
START_TEST(tests_error_calc_1) {
  matrix_t matrix_a, matrix_b, matrix_result;

  for (int i = 0; i < 10; i++) {
    generating_two_different_matrices(&matrix_a, &matrix_b);

    int res = s21_sub_matrix(&matrix_a, &matrix_b, &matrix_result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }
}
END_TEST

START_TEST(tests_error_calc_2) {
  matrix_t matrix_a, matrix_b, matrix_result;
  double invalid_number[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    generating_two_matrices_of_the_same_size(&matrix_a, &matrix_b);

    matrix_a.matrix[0][0] = invalid_number[i];

    int res = s21_sub_matrix(&matrix_a, &matrix_b, &matrix_result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }
}
END_TEST

START_TEST(test_error_incorrect_matrix_1) {
  matrix_t matrix_a, matrix_b, matrix_result;
  matrix_a.matrix = NULL;

  random_matrix_generation(&matrix_b);

  matrix_a.rows = matrix_b.rows;
  matrix_a.columns = matrix_b.columns;

  int res = s21_sub_matrix(&matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_incorrect_matrix_2) {
  matrix_t matrix_a, matrix_b, matrix_result;
  matrix_b.matrix = NULL;

  random_matrix_generation(&matrix_a);

  matrix_b.rows = matrix_a.rows;
  matrix_b.columns = matrix_a.columns;

  int res = s21_sub_matrix(&matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_incorrect_matrix_3) {
  matrix_t *matrix_a = NULL;
  matrix_t matrix_b, matrix_result;

  random_matrix_generation(&matrix_b);

  int res = s21_sub_matrix(matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_incorrect_matrix_4) {
  matrix_t matrix_a, matrix_result;
  matrix_t *matrix_b = NULL;

  random_matrix_generation(&matrix_a);

  int res = s21_sub_matrix(&matrix_a, matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_incorrect_matrix_5) {
  matrix_t matrix_a, matrix_b;
  matrix_t *matrix_result = NULL;

  generating_two_matrices_of_the_same_size(&matrix_a, &matrix_b);

  int res = s21_sub_matrix(&matrix_a, &matrix_b, matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

//Блок тестов без ошибок
START_TEST(random_correct_tests) {
  matrix_t matrix_a, matrix_b, matrix_result;

  for (int a = 0; a < 10; a++) {
    generating_two_matrices_of_the_same_size(&matrix_a, &matrix_b);

    int res = s21_sub_matrix(&matrix_a, &matrix_b, &matrix_result);

    for (int i = 0; i < matrix_result.rows; i++)
      for (int j = 0; j < matrix_result.columns; j++)
        ck_assert_float_eq_tol(matrix_result.matrix[i][j],
                               matrix_a.matrix[i][j] - matrix_b.matrix[i][j],
                               ACCURACY);

    ck_assert_int_eq(res, CORRECT);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
    s21_remove_matrix(&matrix_result);
  }
}
END_TEST

// Создание набора тестов
Suite *test_s21_sub_matrix(void) {
  Suite *s = suite_create("s21_sub_matrix");
  TCase *tc = tcase_create("s21_sub_matrix");

  tcase_add_test(tc, tests_error_calc_1);
  tcase_add_test(tc, tests_error_calc_2);
  tcase_add_test(tc, test_error_incorrect_matrix_1);
  tcase_add_test(tc, test_error_incorrect_matrix_2);
  tcase_add_test(tc, test_error_incorrect_matrix_3);
  tcase_add_test(tc, test_error_incorrect_matrix_4);
  tcase_add_test(tc, test_error_incorrect_matrix_5);

  tcase_add_test(tc, random_correct_tests);

  suite_add_tcase(s, tc);
  return s;
}
