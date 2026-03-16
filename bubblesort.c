#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void FillDec(int *A, int n);
void FillRand(int *A, int n);
int CheckSum(int *A, int n);
int RunNumber(int *A, int n);
void draw_table(int *data, int *teor_data, int n);
int bubble_sort(int *A, int n);
void sort_testing(int n, int mode, int sort);
#define MAX_NUM 101
int test_num = 1;
int table_data[15];
int teor_trud_data[5];


int main() {
    sort_testing(100, -1, 0);
    sort_testing(100, 0, 0);
    sort_testing(100, 1, 0);
    sort_testing(200, -1, 0);
    sort_testing(200, -0, 0);
    sort_testing(200, 1, 0);
    sort_testing(300, -1, 0);
    sort_testing(300, -0, 0);
    sort_testing(300, 1, 0);
    sort_testing(400, -1, 0);
    sort_testing(400, -0, 0);
    sort_testing(400, 1, 0);
    sort_testing(500, -1, 0);
    sort_testing(500, -0, 0);
    sort_testing(500, 1, 0);
    printf("=================================================\n");

    draw_table(table_data, teor_trud_data, 15);
}

void sort_testing(int n, int mode, int sort) {
    srand(time(NULL));
    int A[n];
    switch (mode) {
        case 0:
            printf("Тест %d: случайный массив из %d чисел.\n", test_num, n);
            FillRand(A, n);
            break;
        case -1:
            printf("Тест %d: убывающий массив из %d чисел.\n", test_num, n);
            FillDec(A, n);
            break;
        case 1:
            printf("Тест %d: возрастающий массив из %d чисел.\n", test_num, n);
            Fillinc(A, n);
            break;
        default:
            printf("Указан неверный параметр.\n");
    }

    int controlsum = CheckSum(A, n);
    int trud;
    int teor_trud = ((n * n - n) / 2) + (3 * (n * n - n) / 4);
    trud = bubble_sort(A, n);
    if ((controlsum == CheckSum(A, n)) && (RunNumber(A, n) == 1)) {
        printf("Массив успешно отсортирован по возрастанию.\n");
    } else {
        printf("Массив не удалось отсортировать. Контрольная сумма до = %d, после = %d. Количество серий = %d (должно быть 1).\n", controlsum, CheckSum(A, n), RunNumber(A, n));
    }
    printf("Теоретическая трудоемкость = %d. Фактическая = %d.\n\n", teor_trud, trud);
    teor_trud_data[n / 100 - 1] = teor_trud;
    table_data[test_num - 1] = trud;
    test_num++;
}

void PrintMas(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void Fillinc(int *A, int n) {
    for (int i = 1; i <= n; i++) {
        A[i - 1] = i;
    }   
}
void FillDec(int *A, int n) {
    for (int i = 0; i < n ; i++) {
        A[i] = n - i;
    }   
}

void FillRand(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % MAX_NUM;
    }
}

int CheckSum(int *A, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

int RunNumber(int *A, int n) {
    int count = 1;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            count++;
        }
    }
    return count;
}

int bubble_sort(int *A, int n){
    int M = 0;
    int C = 0;
    int tmp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            C++;
            if (A[j] < A[j-1]) {
                tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
                M += 3;
            }
        }
    }
    printf("M = %d, C = %d.\n", M, C);
    return M + C;
}

void draw_table(int *data, int *teor_data, int n){
    printf("-------------------------------------------------------------------------\n");
    printf("| N\t| M+C(t)\t|\t\tMf+Cf\t\t\t\t|\n");
    printf("|\t|\t\t|------------------------------------------------\n");
    printf("|\t| \t\t| Убыв.\t\t| Случ.\t\t| Возр. \t|\n");
    printf("-------------------------------------------------------------------------\n");
    int i = 0; 
    for (int s = 1; s <= 5; s++) {
        printf("| %d\t| %-6d\t|", s * 100, teor_data[s - 1]);
        for (; i < s * 3; i++) {
            printf(" %-6d\t|", data[i]);
        }
        printf("\n");
        printf("-------------------------------------------------------------------------\n");
    }

}