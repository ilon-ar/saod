#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void FillDec(int *A, int n);
void FillRand(int *A, int n);
int CheckSum(int *A, int n);
int RunNumber(int *A, int n);
void draw_table(int *data, int n);
int bubble_sort(int *A, int n);
int shaker_sort(int *A, int n);
int SelectSort(int *A, int n);
int insert_sort(int *A, int n);
void sort_testing(int n, int mode, int sort);
#define MAX_NUM 101
int test_num = 1;
int table_data[20];

int main() {
    srand(time(NULL));
    sort_testing(100, 0, 2);
    sort_testing(100, 0, 0);
    sort_testing(100, 0, 1);
    sort_testing(100, 0, 3);
    sort_testing(200, 0, 2);
    sort_testing(200, 0, 0);
    sort_testing(200, 0, 1);
    sort_testing(200, 0, 3);
    sort_testing(300, 0, 2);
    sort_testing(300, 0, 0);
    sort_testing(300, 0, 1);
    sort_testing(300, 0, 3);
    sort_testing(400, 0, 2);
    sort_testing(400, 0, 0);
    sort_testing(400, 0, 1);
    sort_testing(400, 0, 3);
    sort_testing(500, 0, 2);
    sort_testing(500, 0, 0);
    sort_testing(500, 0, 1);
    sort_testing(500, 0, 3);
    draw_table(table_data, 20);

}

void sort_testing(int n, int mode, int sort) { //sort : 0 - bubble, 1 - shaker, 2 - select, 3 - insert
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
    int teor_trud;
    switch(sort) {
        case 0:
            printf("Bubble Sort: ");
            teor_trud = ((n * n - n) / 2) + (3 * (n * n - n) / 4);
            trud = bubble_sort(A, n);
            break;
        case 1:
            printf("Shaker Sort: ");
            teor_trud = ((n * n - n) / 2) + (3 * (n * n - n) / 4);;
            trud = shaker_sort(A, n);
            break;
        case 2:
            printf("Select Sort: ");
            teor_trud = 3 * (n - 1) + ((n * n - n) / 2);
            trud = SelectSort(A, n);
            break;
        case 3: 
            printf("Insert Sort: ");
            teor_trud = n * n + n - 2;
            trud = insert_sort(A, n);
            break;

        default:
            printf("Неизвестный метод сортировки.\n");
            return;
    }
    
    if ((controlsum == CheckSum(A, n)) && (RunNumber(A, n) == 1)) {
        printf("Массив успешно отсортирован по возрастанию.\n");
    } else {
        printf("Массив не удалось отсортировать. Контрольная сумма до = %d, после = %d. Количество серий = %d (должно быть 1).\n", controlsum, CheckSum(A, n), RunNumber(A, n));
    }
    printf("Теоретическая трудоемкость = %d. Фактическая = %d.\n\n", teor_trud, trud);
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

int shaker_sort(int *A, int n) {
    int M = 0, C = 0, L = 0, R = n, k = n, tmp;
    do {
        for (int j = R; j >= L + 1; j--) {
            C++;
            if (A[j] < A[j-1]) {
                M += 3;
                tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
                k = j;
            }
        }
        L = k;
        for (int j = L; j <= R - 1; j++) {
            C++;
            if (A[j] > A[j+1]) {
                M += 3;
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                k = j;
            }
        }
        R = k;
    } while (L < R);
    printf("M = %d, C = %d.\n", M, C);
    return M + C;
}
int insert_sort(int *A, int n) {
    int M = 0, C = 0, tmp, j;
    for (int i = 1; i < n; i++) {
        tmp = A[i]; M++;      
        for (j = i - 1; ++C && tmp < A[j] && j >= 0; j--) {
            A[j + 1] = A[j]; M++;
            
        }
        A[j + 1] = tmp; M++;
    }
    printf("M = %d, C = %d.\n", M, C);
    return M + C;
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
void draw_table(int *data,  int n){
    printf("-------------------------------------------------------------------------\n");
    printf("| N\t|\t\tMf+Cf\t\t\t\t\t\t|\n");
    printf("|\t|----------------------------------------------------------------\n");
    printf("|\t| Select \t| Bubble \t| Shaker\t| Insert \t|\n");
    printf("-------------------------------------------------------------------------\n");
    int i = 0; 
    for (int s = 1; s <= 5; s++) {  
        printf("| %d\t|", s * 100);
        for (; i < s * 4; i++) {
            printf(" %-6d\t|", data[i]);
        }
        printf("\n");
        printf("-------------------------------------------------------------------------\n");
    }

}