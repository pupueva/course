#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <locale.h> 
#include <time.h> 

// ��������� ������� 
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
    puts("*�������� ������ �� ���������� \"������ ���������������� � ��������������\" *");
    puts("*����:\"���������� ������������� � ������������ �������\"                   *");
    puts("*���������:�������.�.�, ������ ���-241                                    *");
    puts("*                                                                         *");
    puts("***************************************************************************");

    puts("*���������� ������������� ��������� � ������� � ������,                 *"); 
    puts("*��������� �������� ����� �� ������ ������������.                       *");
    puts("*                                                                       *"); 
    puts("*�������� �����-�������� ������������ � ������� � ����������� � ������  *");
    puts("*************************************************************************");

        while (1) {
            printf("\n����:\n");
            printf("1. ������� �������\n");
            printf("2. ������� �������\n");
            printf("3. ���������� ���������� ������������� ��������� � ������� � ������\n");
            printf("4. ����� �������� �����\n");
            printf("5. ��������� ���������\n");
            printf("�������� ��������: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("������� ���������� ����� � �������� ����� ������ ��� Enter: ");
                scanf("%d %d", &rows, &cols);

                // ��������� ������ 
                matrix = (int**)malloc(rows * sizeof(int*));
                if (!matrix) {
                    printf("������ ��������� ������ ��� �����!\n");
                    return 1;
                }

                for (int i = 0; i < rows; i++) {
                    matrix[i] = (int*)malloc(cols * sizeof(int));
                    if (!matrix[i]) {
                        printf("������ ��������� ������ ��� ��������!\n");
                        for (int j = 0; j < i; j++) {
                            free(matrix[j]);
                        }
                        free(matrix);
                        return 1;
                    }
                }

                printf("�������� ������ �������������:\n1. ��������� �����\n2. ���� � �������\n");
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
                    printf("������� �� ����������������.\n");
                }
                break;

            case 3:
                if (matrix) {
                    matrix = count_negatives_in_rows_with_zero(matrix, rows, cols);
                }
                else {
                    printf("������� �� ����������������.\n");
                }
                break;

            case 4:
                if (matrix) {
                    matrix = find_saddle_points(matrix, rows, cols);
                }
                else {
                    printf("������� �� ����������������.\n");
                }
                break;

            case 5:
                // ����������� ������ ����� �����������
                if (matrix) {
                    for (int i = 0; i < rows; i++) {
                        free(matrix[i]);
                    }
                    free(matrix);
                }
                printf("���������� ���������.\n");
                return 0;

            default:
                printf("������������ ����. ��������� �������.\n");
            }
        }
        return 0;
    }

    // ���� ������� � �������
    int** input_matrix(int** matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("[%d][%d]: ", i + 1, j + 1);
                scanf("%d", &matrix[i][j]);
            }
        }
        return matrix;
    }

    // ��������� ��������� �������
    int** generate_matrix(int** matrix, int rows, int cols, int min, int max) {
        srand(time(NULL));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = rand() % (max - min + 1) + min;
            }
        }
        return matrix;
    }

    // ������ �������
    void print_matrix(int** matrix, int rows, int cols) {
        printf("�������:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%4d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // ������� ������������� ��������� � ������� � ������
    int** count_negatives_in_rows_with_zero(int** matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            int has_zero = 0, negative_count = 0;
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) has_zero = 1;
                if (matrix[i][j] < 0) negative_count++;
            }
            if (has_zero) {
                printf("������ %d �������� %d ������������� ���������.\n", i + 1, negative_count);
            }
        }
        return matrix;
    }

    // ����� �������� �����
    int** find_saddle_points(int** matrix, int rows, int cols) {
        printf("�������� �����:\n");
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
                    printf("�������� �����: [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                    found = 1;
                }
            }
        }

        if (!found) printf("�������� ����� �� �������.\n");
        return matrix;
    }
