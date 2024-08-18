#include "testing.h"

// Тесты для функции s21_transpose

// Блок тестов, в результате которых должна быть ошибкa
START_TEST(test_error_incorrect_matrix_1) {
  matrix_t *matrix_a = NULL;
  matrix_t result;

  int res = s21_transpose(matrix_a, &result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_incorrect_matrix_2) {
  matrix_t matrix_a;
  matrix_t *result = NULL;

  random_matrix_generation(&matrix_a);

  int res = s21_transpose(&matrix_a, result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix_a);
}
END_TEST

START_TEST(test_error_incorrect_matrix_3) {
  matrix_t matrix_a, result;
  matrix_a.matrix = NULL;
  matrix_a.rows = 2;
  matrix_a.columns = 3;

  int res = s21_transpose(&matrix_a, &result);

  s21_remove_matrix(&matrix_a);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tests_error_calc) {
  matrix_t matrix_a, result;
  double invalid_num[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    random_matrix_generation(&matrix_a);
    matrix_a.matrix[0][0] = invalid_num[i];

    int res = s21_transpose(&matrix_a, &result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
  }
}
END_TEST

// Блок тестов без ошибок
START_TEST(random_correct_tests) {
  matrix_t matrix_a, result;

  for (int i = 0; i < 10; i++) {
    random_matrix_generation(&matrix_a);

    int res = s21_transpose(&matrix_a, &result);

    ck_assert_int_eq(res, CORRECT);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&result);
  }
}
END_TEST

// Создание набора тестов
Suite *test_s21_transpose(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc = tcase_create("s21_transpose");

  tcase_add_test(tc, test_error_incorrect_matrix_1);
  tcase_add_test(tc, test_error_incorrect_matrix_2);
  tcase_add_test(tc, test_error_incorrect_matrix_3);
  tcase_add_test(tc, tests_error_calc);

  tcase_add_test(tc, random_correct_tests);

  suite_add_tcase(s, tc);
  return s;
}
