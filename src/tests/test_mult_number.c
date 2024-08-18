#include "testing.h"

// Тесты для функции s21_mult_number

// Блок тестов, в результате которых должна быть ошибка

START_TEST(tests_error_calc_1) {
  matrix_t matrix_a, matrix_result;
  double invalid_num[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    double num = ((double)rand() / RAND_MAX) * 201 - 100;
    random_matrix_generation(&matrix_a);

    matrix_a.matrix[0][0] = invalid_num[i];

    int res = s21_mult_number(&matrix_a, num, &matrix_result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
  }
}
END_TEST

START_TEST(tests_error_calc_2) {
  matrix_t matrix_a, matrix_result;
  double invalid_num[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    random_matrix_generation(&matrix_a);

    double num = invalid_num[i];

    int res = s21_mult_number(&matrix_a, num, &matrix_result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
  }
}
END_TEST

START_TEST(tests_error_calc_3) {
  matrix_t matrix_a, matrix_result;
  double invalid_num[2] = {1e308, -1e308};

  for (int i = 0; i < 2; i++) {
    random_matrix_generation(&matrix_a);
    matrix_a.matrix[0][0] = 1e308;

    double num = invalid_num[i];

    int res = s21_mult_number(&matrix_a, num, &matrix_result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
  }
}
END_TEST

START_TEST(test_error_1) {
  matrix_t *matrix_a = NULL;
  matrix_t matrix_result;
  double num = ((double)rand() / RAND_MAX) * 201 - 100;

  int res = s21_mult_number(matrix_a, num, &matrix_result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_2) {
  matrix_t matrix_a;
  matrix_t *matrix_result = NULL;
  double num = ((double)rand() / RAND_MAX) * 201 - 100;

  random_matrix_generation(&matrix_a);

  int res = s21_mult_number(&matrix_a, num, matrix_result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix_a);
}
END_TEST

START_TEST(test_error_3) {
  matrix_t matrix_a, matrix_result;
  double num = ((double)rand() / RAND_MAX) * 201 - 100;

  matrix_a.matrix = NULL;

  int res = s21_mult_number(&matrix_a, num, &matrix_result);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

//Блок тестов без ошибок
START_TEST(random_correct_tests) {
  matrix_t matrix_a, matrix_result;

  for (int a = 0; a < 10; a++) {
    double num = ((double)rand() / RAND_MAX) * 201 - 100;

    random_matrix_generation(&matrix_a);

    int res = s21_mult_number(&matrix_a, num, &matrix_result);

    for (int i = 0; i < matrix_a.rows; i++)
      for (int j = 0; j < matrix_a.columns; j++)
        ck_assert_double_eq_tol(matrix_result.matrix[i][j],
                                matrix_a.matrix[i][j] * num, ACCURACY);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_result);

    ck_assert_int_eq(res, CORRECT);
  }
}
END_TEST

// Создание набора тестов
Suite *test_s21_mult_number(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("s21_mult_number");

  tcase_add_test(tc, tests_error_calc_1);
  tcase_add_test(tc, tests_error_calc_2);
  tcase_add_test(tc, tests_error_calc_3);
  tcase_add_test(tc, test_error_1);
  tcase_add_test(tc, test_error_2);
  tcase_add_test(tc, test_error_3);

  tcase_add_test(tc, random_correct_tests);

  suite_add_tcase(s, tc);
  return s;
}
