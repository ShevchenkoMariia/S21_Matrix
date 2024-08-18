#ifndef S21_HELPER_FUNCTIONS_H
#define S21_HELPER_FUNCTIONS_H

// Функции-помощники для создания библиотеки s21_matrix.a

#include "s21_matrix.h"

// Проверяем, что данные матрицы одинакового размера
int equal_size_of_the_matrices(matrix_t *A, matrix_t *B);

// Проверяем, что матрица, с которой собираемся работать, имеет не NULL
// указатели
int correct_pointer(matrix_t *pointer);

// Проверяем, что из данной структуры можно создать новую матрицу
int correct_structure(matrix_t *structure);

// Проверяем, что в данной матрице все значения корректные и с ней можно
// работать
int correct_matrix(matrix_t *structure);

// Находим минор матрицы
int finding_a_minor_for_a_matrix(matrix_t *A, int row_for_deletion,
                                 int column_for_deletion, matrix_t *submatrix);

#endif
