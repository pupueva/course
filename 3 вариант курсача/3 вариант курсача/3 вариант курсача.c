#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <locale.h> 
#include <time.h> 

// Прототипы функций 
int** input_matrix(int** matrix, int rows, int cols);
int** generate_matrix(int** matrix, int rows, int cols, int min, int max);
void print_matrix(int** matrix, int rows, int cols);
int** count_negatives_in_rows_with_zero(int** matrix, int rows, int cols);
int** find_saddle_points(int** matrix, int rows, int cols);

int main() {
    setlocale(LC_CTYPE, "RUS");
    int rows, cols, choice, randomize;
    int** matrix = NULL;

    puts("\n***************************************************************************");
    puts("*                                                                         *");
    puts("*Курсовой проект по дисциплине \"основы программирования и алгоритмизации\" *");
    puts("*Тема:\"Реализация динамического и многомерного массива\"                   *");
    puts("*Выполнила:Пуляева.Л.Ю, группа бИД-241                                    *");
    puts("*                                                                         *");
    puts("***************************************************************************");

    puts("*количество отрицательных элементов в строках с нулями,                 *"); 
    puts("*найденные седловые точки по выбору пользователя.                       *");
    puts("*                                                                       *"); 
    puts("*Седловые точки-элементы максимальные в столбце и минимальные в строке  *");
    puts("*************************************************************************");

        while (1) {
            printf("\nМеню:\n");
            printf("1. Создать матрицу\n");
            printf("2. Вывести матрицу\n");
            printf("3. Подсчитать количество отрицательных элементов в строках с нулями\n");
            printf("4. Найти седловые точки\n");
            printf("5. Завершить программу\n");
            printf("Выберите действие: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Введите количество строк и столбцов через пробел или Enter: ");
                scanf("%d %d", &rows, &cols);

                // Выделение памяти 
                matrix = (int**)malloc(rows * sizeof(int*));
                if (!matrix) {
                    printf("Ошибка выделения памяти для строк!\n");
                    return 1;
                }

                for (int i = 0; i < rows; i++) {
                    matrix[i] = (int*)malloc(cols * sizeof(int));
                    if (!matrix[i]) {
                        printf("Ошибка выделения памяти для столбцов!\n");
                        for (int j = 0; j < i; j++) {
                            free(matrix[j]);
                        }
                        free(matrix);
                        return 1;
                    }
                }

                printf("Выберите способ инициализации:\n1. Случайные числа\n2. Ввод с консоли\n");
                scanf("%d", &randomize);

                if (randomize == 1) {
                    matrix = generate_matrix(matrix, rows, cols, -10, 10);
                }
                else {
                    matrix = input_matrix(matrix, rows, cols);
                }
                break;

            case 2:
                if (matrix) {
                    print_matrix(matrix, rows, cols);
                }
                else {
                    printf("Матрица не инициализирована.\n");
                }
                break;

            case 3:
                if (matrix) {
                    matrix = count_negatives_in_rows_with_zero(matrix, rows, cols);
                }
                else {
                    printf("Матрица не инициализирована.\n");
                }
                break;

            case 4:
                if (matrix) {
                    matrix = find_saddle_points(matrix, rows, cols);
                }
                else {
                    printf("Матрица не инициализирована.\n");
                }
                break;

            case 5:
                // Освобождаем память перед завершением
                if (matrix) {
                    for (int i = 0; i < rows; i++) {
                        free(matrix[i]);
                    }
                    free(matrix);
                }
                printf("Завершение программы.\n");
                return 0;

            default:
                printf("Некорректный ввод. Повторите попытку.\n");
            }
        }
        return 0;
    }

    // Ввод матрицы с консоли
    int** input_matrix(int** matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("[%d][%d]: ", i + 1, j + 1);
                scanf("%d", &matrix[i][j]);
            }
        }
        return matrix;
    }

    // Генерация случайной матрицы
    int** generate_matrix(int** matrix, int rows, int cols, int min, int max) {
        srand(time(NULL));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = rand() % (max - min + 1) + min;
            }
        }
        return matrix;
    }

    // Печать матрицы
    void print_matrix(int** matrix, int rows, int cols) {
        printf("Матрица:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%4d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // Подсчет отрицательных элементов в строках с нулями
    int** count_negatives_in_rows_with_zero(int** matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            int has_zero = 0, negative_count = 0;
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) has_zero = 1;
                if (matrix[i][j] < 0) negative_count++;
            }
            if (has_zero) {
                printf("Строка %d содержит %d отрицательных элементов.\n", i + 1, negative_count);
            }
        }
        return matrix;
    }

    // Поиск седловых точек
    int** find_saddle_points(int** matrix, int rows, int cols) {
        printf("Седловые точки:\n");
        int found = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int is_min_in_row = 1, is_max_in_col = 1;

                for (int k = 0; k < cols; k++) {
                    if (matrix[i][k] < matrix[i][j]) {
                        is_min_in_row = 0;
                        break;
                    }
                }

                for (int k = 0; k < rows; k++) {
                    if (matrix[k][j] > matrix[i][j]) {
                        is_max_in_col = 0;
                        break;
                    }
                }

                if (is_min_in_row && is_max_in_col) {
                    printf("Седловая точка: [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                    found = 1;
                }
            }
        }

        if (!found) printf("Седловых точек не найдено.\n");
        return matrix;
    }
