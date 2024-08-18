#include "testing.h"

int main() {
  int failed = 0;

  Suite* all_tests_for_s21_matrix[11] = {
      test_s21_calc_complements(), test_s21_create_matrix(),
      test_s21_determinant(),      test_s21_eq_matrix(),
      test_s21_inverse_matrix(),   test_s21_mult_matrix(),
      test_s21_mult_number(),      test_s21_remove_matrix(),
      test_s21_sub_matrix(),       test_s21_sum_matrix(),
      test_s21_transpose()};

  for (int i = 0; i < 11; i++) {
    SRunner* runner = srunner_create(all_tests_for_s21_matrix[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  if (failed == 0)
    printf("\n\033[0;32mTotal errors: %d\033[0m\n", failed);
  else
    printf("\n\033[0;31mTotal errors: %d\033[0m\n", failed);

  return (failed == 0) ? 0 : 1;
}
