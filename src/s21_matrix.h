#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// матрица представлена в виде структуры
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Точность дробной части
#define ACCURACY 0.000001

// Возвращаемое значение для функции s21_eq_matrix и для дополнительных функций
// проверки
#define SUCCESS 1
#define FAILURE 0

/*
 * В остальных случаях каждая функция будет возвращать:
 * 0 - Корректное значение
 * 1 - Ошибка, некорректная матрица
 * 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
 * нельзя провести вычисления и т.д.)
 */
#define CORRECT 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#include "s21_helper_functions.h"

// Создание матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матрицы
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение и вычитание матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число и умножение двух матриц
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы + алгебраическое дополнение
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif
