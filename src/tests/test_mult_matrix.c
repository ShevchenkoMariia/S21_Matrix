#include "testing.h"

// Тесты для функции s21_mult_matrix

// Блок тестов, в результате которых должна быть ошибкa
START_TEST(tests_error_incorrect_matrix_1) {
  matrix_t *matrix_a = NULL;
  matrix_t matrix_b, matrix_result;

  random_matrix_generation(&matrix_b);

  int res = s21_mult_matrix(matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tests_error_incorrect_matrix_2) {
  matrix_t *matrix_b = NULL;
  matrix_t matrix_a, matrix_result;

  random_matrix_generation(&matrix_a);

  int res = s21_mult_matrix(&matrix_a, matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tests_error_incorrect_matrix_3) {
  matrix_t *matrix_result = NULL;
  matrix_t matrix_a, matrix_b;

  generating_two_matrices_for_mult(&matrix_a, &matrix_b);
  int res = s21_mult_matrix(&matrix_a, &matrix_b, matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tests_error_incorrect_matrix_4) {
  matrix_t matrix_a, matrix_b, matrix_result;
  matrix_a.matrix = NULL;

  random_matrix_generation(&matrix_b);
  matrix_a.rows = matrix_b.columns;
  matrix_a.columns = rand() % 100 + 1;

  int res = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tests_error_incorrect_matrix_5) {
  matrix_t matrix_a, matrix_b, matrix_result;
  matrix_b.matrix = NULL;

  random_matrix_generation(&matrix_a);
  matrix_b.rows = matrix_a.columns;
  matrix_b.columns = rand() % 100 + 1;

  int res = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(tests_error_calc_1) {
  matrix_t matrix_a, matrix_b, matrix_result;
  generating_two_matrices_for_mult(&matrix_a, &matrix_b);
  matrix_a.rows += 2;

  int res = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

  matrix_a.rows -= 2;

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

START_TEST(tests_error_calc_2) {
  matrix_t matrix_a, matrix_b, matrix_result;
  generating_two_matrices_for_mult(&matrix_a, &matrix_b);
  matrix_b.columns += 2;

  int res = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

  s21_remove_matrix(&matrix_a);
  s21_remove_matrix(&matrix_b);

  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

START_TEST(tests_error_calc_3) {
  matrix_t matrix_a, matrix_b, matrix_result;
  double invalid_num[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    generating_two_matrices_for_mult(&matrix_a, &matrix_b);
    matrix_a.matrix[0][0] = invalid_num[i];
    int res_1 = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

    ck_assert_int_eq(res_1, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }

  for (int i = 0; i < 3; i++) {
    generating_two_matrices_for_mult(&matrix_a, &matrix_b);
    matrix_b.matrix[0][0] = invalid_num[i];

    int res_2 = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

    ck_assert_int_eq(res_2, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }
}
END_TEST

START_TEST(tests_error_calc_4) {
  matrix_t matrix_a, matrix_b, matrix_result;

  double num[2] = {1e308, -1e308};

  for (int i = 0; i < 2; i++) {
    generating_two_matrices_for_mult(&matrix_a, &matrix_b);

    matrix_a.matrix[0][0] = 1e308;
    matrix_b.matrix[0][0] = num[i];

    int res = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
  }
}
END_TEST

//Блок тестов без ошибок
START_TEST(random_correct_tests) {
  matrix_t matrix_a, matrix_b, matrix_result;

  for (int a = 0; a < 10; a++) {
    generating_two_matrices_for_mult(&matrix_a, &matrix_b);
    int res = s21_mult_matrix(&matrix_a, &matrix_b, &matrix_result);
    for (int i = 0; i < matrix_result.rows; i++) {
      for (int j = 0; j < matrix_result.columns; j++) {
        double num = 0.0f;
        for (int a = 0; a < matrix_a.columns; a++) {
          num += matrix_a.matrix[i][a] * matrix_b.matrix[a][j];
        }
        ck_assert_double_eq_tol(matrix_result.matrix[i][j], num, ACCURACY);
      }
    }
    ck_assert_int_eq(res, CORRECT);

    s21_remove_matrix(&matrix_a);
    s21_remove_matrix(&matrix_b);
    s21_remove_matrix(&matrix_result);
  }
}
END_TEST

START_TEST(test_mult_matrix_1) {
  matrix_t matrix;
  matrix_t result;

  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &matrix);
  matrix.matrix[0][0] = 5;
  matrix.matrix[0][1] = 8;
  matrix.matrix[0][2] = -4;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 9;
  matrix.matrix[1][2] = -5;
  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 7;
  matrix.matrix[2][2] = -3;

  int res = s21_mult_matrix(&matrix, &matrix, &result);
  ck_assert_int_eq(res, CORRECT);

  ck_assert_double_eq(result.matrix[0][0], 57);
  ck_assert_double_eq(result.matrix[0][1], 84);
  ck_assert_double_eq(result.matrix[0][2], -48);
  ck_assert_double_eq(result.matrix[1][0], 64);
  ck_assert_double_eq(result.matrix[1][1], 94);
  ck_assert_double_eq(result.matrix[1][2], -54);
  ck_assert_double_eq(result.matrix[2][0], 50);
  ck_assert_double_eq(result.matrix[2][1], 74);
  ck_assert_double_eq(result.matrix[2][2], -42);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

// Создание набора тестов
Suite *test_s21_mult_matrix(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc = tcase_create("s21_mult_matrix");

  tcase_add_test(tc, tests_error_incorrect_matrix_1);
  tcase_add_test(tc, tests_error_incorrect_matrix_2);
  tcase_add_test(tc, tests_error_incorrect_matrix_3);
  tcase_add_test(tc, tests_error_incorrect_matrix_4);
  tcase_add_test(tc, tests_error_incorrect_matrix_5);
  tcase_add_test(tc, tests_error_calc_1);
  tcase_add_test(tc, tests_error_calc_2);
  tcase_add_test(tc, tests_error_calc_3);
  tcase_add_test(tc, tests_error_calc_4);

  tcase_add_test(tc, test_mult_matrix_1);

  tcase_add_test(tc, random_correct_tests);

  suite_add_tcase(s, tc);
  return s;
}
