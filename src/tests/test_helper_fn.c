#include "testing.h"

// Генерация рандомной матрицы
void random_matrix_generation(matrix_t *matrix) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, matrix);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      // Генерируем дробное число в диапазоне от -100 до +100
      double num = ((double)rand() / RAND_MAX) * 201 - 100;
      matrix->matrix[i][j] = num;
    }
  matrix->rows = rows;
  matrix->columns = columns;
}

// Генерация двух разных рандомных матриц
void generating_two_different_matrices(matrix_t *matrix_A, matrix_t *matrix_B) {
  random_matrix_generation(matrix_A);
  random_matrix_generation(matrix_B);
}

// Генерация двух идентичных матриц
void generating_two_identical_matrices(matrix_t *matrix_A, matrix_t *matrix_B) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, matrix_A);
  s21_create_matrix(rows, columns, matrix_B);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      // Генерируем дробное число в диапазоне от -100 до +100
      double num = ((double)rand() / RAND_MAX) * 201 - 100;
      matrix_A->matrix[i][j] = num;
      matrix_B->matrix[i][j] = num;
    }
}

// Генерация двух одинаковых по размеру матриц, но разных по наполнению
void generating_two_matrices_of_the_same_size(matrix_t *matrix_A,
                                              matrix_t *matrix_B) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, matrix_A);
  s21_create_matrix(rows, columns, matrix_B);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      // Генерируем дробное число в диапазоне от -100 до +100
      double num = ((double)rand() / RAND_MAX) * 201 - 100;
      matrix_A->matrix[i][j] = num;
      num = ((double)rand() / RAND_MAX) * 201 - 100;
      matrix_B->matrix[i][j] = num;
    }
}

// Генерация двух матриц, где A->rows == B->columns
void generating_two_matrices_for_mult(matrix_t *matrix_A, matrix_t *matrix_B) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, matrix_A);
  s21_create_matrix(columns, rows, matrix_B);

  for (int i = 0; i < matrix_A->rows; i++) {
    for (int j = 0; j < matrix_A->columns; j++) {
      // Генерируем дробное число в диапазоне от -100 до +100
      double num = ((double)rand() / RAND_MAX) * 201 - 100;
      matrix_A->matrix[i][j] = num;
    }
  }
  for (int i = 0; i < matrix_B->rows; i++) {
    for (int j = 0; j < matrix_B->columns; j++) {
      // Генерируем дробное число в диапазоне от -100 до +100
      double num = ((double)rand() / RAND_MAX) * 201 - 100;
      matrix_B->matrix[i][j] = num;
    }
  }
}

// Генерация квадратной матрицы
void generating_a_square_matrix(matrix_t *A) {
  int rows = rand() % 100 + 1;
  int columns = rows;
  s21_create_matrix(rows, columns, A);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      // Генерируем дробное число в диапазоне от -100 до +100
      double num = ((double)rand() / RAND_MAX) * 201 - 100;
      A->matrix[i][j] = num;
    }
  A->rows = rows;
  A->columns = columns;
}
