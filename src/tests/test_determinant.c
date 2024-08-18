#include "testing.h"

// Тесты для функции s21_determinant

// Блок тестов с ошибкой
START_TEST(test_error_1) {
  matrix_t *A = NULL;
  double determinant = 0.0;
  int res = s21_determinant(A, &determinant);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_2) {
  matrix_t A;
  double *determinant = NULL;

  s21_create_matrix(2, 2, &A);

  int res = s21_determinant(&A, determinant);

  ck_assert_int_eq(res, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_error_3) {
  matrix_t A;
  A.matrix = NULL;
  double determinant = 0.0;
  int res = s21_determinant(&A, &determinant);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_error_4) {
  matrix_t A;
  double determinant = 0.0;
  double invalid_number[3] = {INFINITY, -INFINITY, NAN};

  for (int i = 0; i < 3; i++) {
    generating_a_square_matrix(&A);
    A.matrix[0][0] = invalid_number[i];

    int res = s21_determinant(&A, &determinant);

    ck_assert_int_eq(res, CALCULATION_ERROR);

    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(test_error_5) {
  matrix_t A;
  double determinant = 0.0;

  do {
    random_matrix_generation(&A);
  } while (A.rows == A.columns);

  int res = s21_determinant(&A, &determinant);

  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_error_6) {
  matrix_t A;
  double determinant = 0.0;

  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1e308;
  A.matrix[0][1] = 1e308;
  A.matrix[0][2] = 1e308;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 1e308;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 1e308;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = 1e308;

  int res = s21_determinant(&A, &determinant);

  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

// Блок тестов без ошибок
START_TEST(correct_test_1) {
  matrix_t A;
  double determinant = 0.0;

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

  int res = s21_determinant(&A, &determinant);

  ck_assert_double_eq(determinant, -1.0);
  ck_assert_int_eq(res, CORRECT);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(correct_test_2) {
  matrix_t A;
  double determinant = 0.0;

  int rows = 4;
  int columns = 4;

  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 0.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 2.0;
  A.matrix[1][2] = 5.0;
  A.matrix[1][3] = 2.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 5.0;
  A.matrix[2][2] = 2.0;
  A.matrix[2][3] = 3.0;
  A.matrix[3][0] = 4.0;
  A.matrix[3][1] = 5.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 1.0;

  int res = s21_determinant(&A, &determinant);

  ck_assert_double_eq(determinant, -180.0);
  ck_assert_int_eq(res, CORRECT);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(correct_test_3) {
  matrix_t A;
  double determinant = 0.0;

  int rows = 1;
  int columns = 1;

  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 2.0;

  int res = s21_determinant(&A, &determinant);

  ck_assert_double_eq(determinant, 2.0);
  ck_assert_int_eq(res, CORRECT);

  s21_remove_matrix(&A);
}
END_TEST

// Создание набора тестов
Suite *test_s21_determinant(void) {
  Suite *s = suite_create("s21_determinant");
  TCase *tc = tcase_create("s21_determinant");

  tcase_add_test(tc, test_error_1);
  tcase_add_test(tc, test_error_2);
  tcase_add_test(tc, test_error_3);
  tcase_add_test(tc, test_error_4);
  tcase_add_test(tc, test_error_5);
  tcase_add_test(tc, test_error_6);

  tcase_add_test(tc, correct_test_1);
  tcase_add_test(tc, correct_test_2);
  tcase_add_test(tc, correct_test_3);

  suite_add_tcase(s, tc);
  return s;
}
