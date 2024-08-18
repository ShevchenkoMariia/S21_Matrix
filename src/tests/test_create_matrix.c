#include "testing.h"

// Тесты для функции s21_create_matrix

//Блок тестов, в результате которых должна быть ошибка INCORRECT_MATRIX (1)
START_TEST(test_error_1) {
  matrix_t matrix;
  int res = s21_create_matrix(0, 2, &matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_2) {
  matrix_t matrix;
  int res = s21_create_matrix(2, 0, &matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_3) {
  matrix_t *matrix = NULL;
  int res = s21_create_matrix(2, 3, matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_4) {
  matrix_t matrix;
  int res = s21_create_matrix(2, -1, &matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_5) {
  matrix_t matrix;
  int res = s21_create_matrix(-1, 3, &matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

//Блок тестов, в результате которых будет выделена память для матриц
START_TEST(correct_test_1) {
  matrix_t matrix;
  int res = s21_create_matrix(1, 1, &matrix);

  ck_assert_int_eq(res, CORRECT);
  ck_assert_int_eq(matrix.rows, 1);
  ck_assert_int_eq(matrix.columns, 1);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(correct_test_2) {
  matrix_t matrix;
  int res = s21_create_matrix(4, 6, &matrix);

  ck_assert_int_eq(res, CORRECT);
  ck_assert_int_eq(matrix.rows, 4);
  ck_assert_int_eq(matrix.columns, 6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(correct_test_3) {
  matrix_t matrix;
  int res = s21_create_matrix(100, 100, &matrix);

  ck_assert_int_eq(res, CORRECT);
  ck_assert_int_eq(matrix.rows, 100);
  ck_assert_int_eq(matrix.columns, 100);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(random_correct_test) {
  matrix_t matrix;
  for (int a = 0; a < 10; a++) {
    int rows = rand() % 100 + 1;
    int columns = rand() % 100 + 1;

    int res = s21_create_matrix(rows, columns, &matrix);

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) {
        matrix.matrix[i][j] = 1.12345678;
        ck_assert_ldouble_eq_tol(1.12345678, matrix.matrix[i][j], ACCURACY);
      }

    ck_assert_int_eq(res, CORRECT);
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);
    s21_remove_matrix(&matrix);
  }
}
END_TEST

// Создание набора тестов
Suite *test_s21_create_matrix(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("s21_create_matrix");

  tcase_add_test(tc, test_error_1);
  tcase_add_test(tc, test_error_2);
  tcase_add_test(tc, test_error_3);
  tcase_add_test(tc, test_error_4);
  tcase_add_test(tc, test_error_5);

  tcase_add_test(tc, correct_test_1);
  tcase_add_test(tc, correct_test_2);
  tcase_add_test(tc, correct_test_3);
  tcase_add_test(tc, random_correct_test);

  suite_add_tcase(s, tc);
  return s;
}
