#include "s21_helper_functions.h"

// Проверяем, что данные матрицы одинакового размера
int equal_size_of_the_matrices(matrix_t *A, matrix_t *B) {
  return ((A->rows == B->rows) && (A->columns == B->columns)) ? SUCCESS
                                                              : FAILURE;
}

// Проверяем, что матрица, с которой собираемся работать, имеет не NULL
// указатели
int correct_pointer(matrix_t *pointer) {
  int check = SUCCESS;
  if (pointer != NULL) {
    if (pointer->matrix == NULL) check = FAILURE;
  } else
    check = FAILURE;
  return check;
}

// Проверяем, что из данной структуры можно создать новую матрицу
int correct_structure(matrix_t *structure) {
  int check = correct_pointer(structure);
  return (check && structure->rows > 0 && structure->columns > 0) ? SUCCESS : FAILURE;
}

// Проверяем, что в данной матрице все значения корректные и с ней можно
// работать
int correct_matrix(matrix_t *structure) {
  int check = SUCCESS;
  for (int i = 0; i < structure->rows; i++)
    for (int j = 0; j < structure->columns; j++)
      if (isnan(structure->matrix[i][j]) || isinf(structure->matrix[i][j]))
        check = FAILURE;
  return check ? SUCCESS : FAILURE;
}

// Находим минор матрицы
int finding_a_minor_for_a_matrix(matrix_t *A, int row_for_deletion,
                                 int column_for_deletion, matrix_t *submatrix) {
  int error = CORRECT;
  submatrix->columns = A->columns - 1;
  submatrix->rows = A->rows - 1;

  // Заполняем подматрицу
  for (int i = 0, a = 0; i < submatrix->rows && error == CORRECT; i++, a++)
    for (int j = 0, b = 0; j < submatrix->columns && error == CORRECT;
         j++, b++) {
      if (a == row_for_deletion) a++;
      if (b == column_for_deletion) b++;
      submatrix->matrix[i][j] = A->matrix[a][b];
    }
  return error;
}
