#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Fillinc(int *A, int n);
void PrintMas(int *A, int n, int L, int R);
void FillDec(int *A, int n);
void FillRand(int *A, int n);
int CheckSum(int *A, int n);
int RunNumber(int *A, int n);
void draw_table(int *data);
void draw_rec_table(int *data);
void sort_testing(int n, int mode, int v);
int QuickSortV1(int *A, int n, int L, int R, int *C, int *M, int depth);
int QuickSortV2(int *A, int n, int L, int R, int *C, int *M, int depth);

int test_num = 1;
int table_data[15];
int tabel_rec_data[30];


int main() {
    srand(time(NULL));
    for (int v = 1; v <= 2; v++) {
        for (int n = 100; n < 501; n += 100) {
            for (int m = -1; m <= 1; m++) {
                sort_testing(n, m, v);
            }
        }
    }
    
    draw_table(table_data);
    printf("\n");
    draw_rec_table(tabel_rec_data);
    return 0;
}

void sort_testing(int n, int mode, int v) { 
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
    int teor_trud = 3 * (n - 1) + (n * n + 5 * n + 4) / 2;
    int C = 0, M = 0;
    int controlsum = CheckSum(A, n);
    int recursion_depth;
    printf("Quick Sort(Метод Хоара) Версия %d.\n", v);
    if (v == 1) recursion_depth = QuickSortV1(A, n, 0, n - 1, &C, &M, 1);
    else recursion_depth = QuickSortV2(A, n, 0, n - 1, &C, &M, 1);
    int trud = C + M;
    
    if ((controlsum == CheckSum(A, n)) && (RunNumber(A, n) == 1)) {
        printf("Массив успешно отсортирован по возрастанию.\n");
    } else {
        printf("Массив не удалось отсортировать. Контрольная сумма до = %d, после = %d. Количество серий = %d (должно быть %d).\n", controlsum, CheckSum(A, n), RunNumber(A, n), 1);
    }
    printf("Теоретическая трудоемкость (Максимальная) = %d. Фактическая = %d. Достигнутая глубина рекурсии = %d.\n\n", teor_trud, trud, recursion_depth);
    printf("\n");
    if (test_num <= 15) table_data[test_num - 1] = trud;
    tabel_rec_data[test_num - 1] = recursion_depth;
    test_num++;
}

void PrintMas(int *A, int n, int L, int R) {
    for (int i = L; i < R; i++) {
        printf("%d ", A[i]);
    }
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
        A[i] = rand() % (n * 2 + 1);
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

int QuickSortV1(int *A, int n, int L, int R, int *C, int *M, int depth) {
    (*M)++;
    int x = A[L], i = L, j = R, tmp;
    while (i <= j) {
        while (++(*C) && A[i] < x) i++;
        while (++(*C) && A[j] > x) j--;
        if (i <= j) {
            *M += 3;
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            i++; j--;
        }
    }
    int d1 = depth, d2 = depth;
    if (L < j) d1 = QuickSortV1(A, n, L, j, C, M, depth + 1);
    if (i < R) d2 = QuickSortV1(A, n, i, R, C, M, depth + 1);
    return (d1 > d2) ? d1 : d2; 
}

int QuickSortV2(int *A, int n, int L, int R, int *C, int *M, int depth) {
    int max_depth = depth;
    while (L < R) {
        (*M)++;
        int x = A[L], i = L, j = R, tmp;
        while (i <= j) {
            while (++(*C) && A[i] < x) i++;
            while (++(*C) && A[j] > x) j--;
            if (i <= j) {
                *M += 3;
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
                i++; j--;
            }
        }
        if (j - L < R - i) {
            int d = QuickSortV2(A, n, L, j, C, M, depth + 1);
            if (d > max_depth) max_depth = d;
            L = i;
        } else {
            int d = QuickSortV2(A, n, i, R, C, M, depth + 1);
            if (d > max_depth) max_depth = d;
            R = j;
        }
    }
    return max_depth;
}

void draw_table(int *data) {
    printf("Трудоемкость метода Хоара\n");
    printf("—————————————————————————————————————————————————————————\n");
    printf("| N\t| \t\tQuick Sort \t\t\t| \n");
    printf("|\t| Убыв.\t\t| Случ.\t\t| Возр.\t\t|\n");
    printf("—————————————————————————————————————————————————————————\n");
    for (int s = 1; s <= 5; s++) {
        printf("| %d\t| %8d\t| %8d\t| %8d\t|\n", s * 100, data[3 * (s - 1)], data[3 * (s - 1) + 1], data[3 * (s - 1) + 2]);
        printf("—————————————————————————————————————————————————————————\n");
    }
}

void draw_rec_table(int *data) {
    printf("Глубина рекурсии сортировки методом Хоара\n");
    printf("—————————————————————————————————————————————————————————\n");
    printf("| N\t| QuickSort1 \t\t| QuickSort2\t\t|\n");
    printf("|\t| Убыв.\t| Случ.\t| Возр.\t| Убыв.\t| Случ.\t| Возр.\t|\n");
    printf("—————————————————————————————————————————————————————————\n");
    for (int s = 1; s <= 5; s++) {
        printf("| %d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\t|\n", s * 100, data[3 * (s - 1)], data[3 * (s - 1) + 1], data[3 * (s - 1) + 2], data[3 * (s - 1) + 15], data[3 * (s - 1) + 16], data[3 * (s - 1) + 17]);
        printf("—————————————————————————————————————————————————————————\n");
    }
}