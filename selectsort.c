#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void FillDec(int *A, int n);
void FillRand(int *A, int n);
int CheckSum(int *A, int n);
int RunNumber(int *A, int n);
int SelectSort(int *A, int n);
void select_sort_testing(int n, int mode, int upgrade); //mode: -1 -> убывающий массив, 0 -> случайный массив,
                                                        //  1 -> возрастающий массив. upgrade: 0 -> стандартный,
                                                        //  1 -> улучшенный.

int upgraded_select_sort(int *A, int n); 
void draw_table(int *data, int n);


#define MAX_NUM 101
int test_num = 1;
int table_data[12];
int main() {
    select_sort_testing(10, -1, 0);
    select_sort_testing(10, 0, 0);
    select_sort_testing(10, 1, 0);
    select_sort_testing(10, -1, 1);
    select_sort_testing(10, 0, 1);
    select_sort_testing(10, 1, 1);
    printf("======================\n");
    select_sort_testing(100, -1, 0);
    select_sort_testing(100, 0, 0);
    select_sort_testing(100, 1, 0);
    select_sort_testing(100, -1, 1);
    select_sort_testing(100, 0, 1);
    select_sort_testing(100, 1, 1);

    // printf("Данные для графика:\n");
    // for (int i = 1; i <= 1000; i++) {
    //     int A[i];
    //     FillRand(A, i);
    //     printf("%d;%d\n", i, SelectSort(A, i));
    // }

    draw_table(table_data, 12);
    return 0;

}

void select_sort_testing(int n, int mode, int upgrade) {
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
    int teor_trud = 3 * (n - 1) + ((n * n - n) / 2);
    printf("Изначальный массив: \n");
    // PrintMas(A, n);
    printf("Отсортированный массив ");
    if (upgrade == 0) {
        trud = SelectSort(A, n);
    } else {
        printf("(улучшенный метод)");   
        trud = upgraded_select_sort(A, n);
    }
    printf(": \n");
        // PrintMas(A, n);
    if ((controlsum == CheckSum(A, n)) && (RunNumber(A, n) == 1)) {
        printf("Массив успешно отсортирован по возрастанию.\n");
    } else {
        printf("Массив не удалось отсортировать. Контрольная сумма до = %d, после = %d. Количество серий = %d (должно быть 1).\n", controlsum, CheckSum(A, 10), RunNumber(A, 10));
    }
    printf("Теоретическая трудоемкость = %d. Фактическая = %d.\n\n", teor_trud, trud);
    if(test_num <= 12) {
        table_data[test_num - 1] = trud;
    }
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

int SelectSort(int *A, int n) {
    int k; int tmp; int C = 0; int M = 0;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            C++;
            if (A[j] < A[k]) {
                k = j;
            }
        }
        tmp = A[i];
        A[i] = A[k];
        A[k] = tmp;
        M += 3;
    }
    printf("M = %d; C = %d\n", M, C);
    return M + C;
}

int upgraded_select_sort(int *A, int n) {
    int k; int tmp; int C = 0; int M = 0;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            C++;
            if (A[j] < A[k]) {
                k = j;
            }
        }
        if (k != i) {
            tmp = A[i];
            A[i] = A[k];
            A[k] = tmp;
            M += 3;
        }
        
    }
    printf("M = %d; C = %d\n", M, C);
    return M + C;
}

void draw_table(int *data, int n){
    printf("-----------------------------------------------------------------\n");
    printf("| N\t| M+C(t)| \tMf+Cf\t\t| \tMf+Cf(up)\t|\n");
    printf("|\t|\t|------------------------------------------------\n");
    printf("|\t| \t| Убыв.\t| Случ.\t| Возр.\t| Убыв.\t| Случ.\t| Возр. |\n");
    printf("-----------------------------------------------------------------\n");
    printf("| 10\t| 72\t|");
    int i = 0;
    for (; i < n / 2; i++){
        printf(" %d\t|", data[i]);
    }
    
    printf("\n-----------------------------------------------------------------\n");
    printf("| 100\t| 5247\t|");
    for (; i < n; i++){
        printf(" %d\t|", data[i]);
    }
    printf("\n");
    printf("-----------------------------------------------------------------\n");

}

