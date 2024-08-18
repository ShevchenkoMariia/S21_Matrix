#include "testing.h"

// Тесты для функции s21_remove_matrix

// Тесты с некорректной матрицей
START_TEST(test_error) {
  matrix_t matrix;
  matrix.rows = 10;
  matrix.columns = 7;
  matrix.matrix = NULL;

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

// Тесты с корректной матрицей
START_TEST(random_tests) {
  matrix_t matrix;
  random_matrix_generation(&matrix);

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(correct_test_2) {
  matrix_t matrix;
  random_matrix_generation(&matrix);

  matrix.matrix[0][0] = INFINITY;

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

// Создание набора тестов
Suite *test_s21_remove_matrix(void) {
  Suite *s = suite_create("s21_remove_matrix");
  TCase *tc = tcase_create("s21_remove_matrix");

  tcase_add_test(tc, test_error);
  tcase_add_test(tc, random_tests);
  tcase_add_test(tc, correct_test_2);

  suite_add_tcase(s, tc);
  return s;
}
