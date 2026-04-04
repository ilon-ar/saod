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
void draw_table_heap(int *data, int n, int *teor_data);
void draw_table_sort(int *data, int n);
void sort_testing(int n, int mode);
void heap_testing();
char IsHeap(int *A, int n, int L, int R);
int AddToHeap(int *A, int n, int L, int R, int *C, int *M);
int HeapSort(int *A, int n);


int test_num = 1;
int table_data_heap[15];
int table_data_heap_teor[5];
int table_data_sort[15];

int main() {
    srand(time(NULL));
    for (int n = 100; n < 501; n += 100) {
        for (int mode = -1; mode < 2; mode++) {
            sort_testing(n, mode);
        }   
    }
    draw_table_heap(table_data_heap, 15, table_data_heap_teor);
    draw_table_sort(table_data_sort, 15);
    return 0;
}

void sort_testing(int n, int mode) { 
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
    int trud = HeapSort(A, n);
    int teor_trud = n * log2(n) + 6.5 * n + 4 + 2 * n * log2(n) + n + 2;
    
    
    if ((controlsum == CheckSum(A, n)) && (RunNumber(A, n) == n)) {
        printf("Массив успешно отсортирован по убыванию.\n");
    } else {
        printf("Массив не удалось отсортировать. Контрольная сумма до = %d, после = %d. Количество серий = %d (должно быть %d).\n", controlsum, CheckSum(A, n), RunNumber(A, n), n);
    }
    printf("Теоретическая трудоемкость = %d. Фактическая = %d.\n\n", teor_trud, trud);
    printf("\n");
    table_data_sort[test_num - 1] = trud;
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
        if (A[i] >= A[i + 1]) {
            count++;
        }
    }
    return count;
}

char IsHeap(int *A, int n, int L, int R) {
    for (int i = L; i < (R - 1) / 2; i++) {
        if (2 * i + 1 < n && A[i] > A[2 * i + 1]) {
            return 0;
        }
        if (2 * i + 2 < n && A[i] > A[2 * i + 2]) {
            return 0;
        }
    }
    return 1;
}

int AddToHeap(int *A, int n, int L, int R, int *C, int *M) {
    int mnac = *M, cnac = *C;
   
    int x = A[L - 1];
    int i = L - 1, j;
    while (1) {
        j = 2 * i + 1;
        if (j >= R) break;
        if (++(*C) && j + 1 < R && A[j + 1] <= A[j]) j++;
        if (++(*C) && x <= A[j]) break;
        (*M)++;
        A[i] = A[j];
        i = j;
    }
    (*M)++;
    A[i] = x;
    int Mt = (int)log2(R * 1.0 / L) + 2, Ct = 2 * log2(R / L);
    if (table_data_heap_teor[n / 100 - 1] < Mt + Ct) {
        table_data_heap_teor[n / 100 - 1] = Mt + Ct;
    }
    if (table_data_heap[test_num - 1] < *M + *C - mnac - cnac) {
        table_data_heap[test_num - 1] = *M + *C - mnac - cnac;
    }
    
}

int HeapSort(int *A, int n) {
    int C = 0, M = 0;
    int L = n / 2;
    while (L >= 1) {
        AddToHeap(A, n, L, n, &C, &M);
        L--;
    }
    int R = n, tmp;
    while (R > 1) {
        tmp = A[0];
        A[0] = A[R - 1];
        A[R - 1] = tmp;
        M += 3;
        R--;
        AddToHeap(A, n, 1, R, &C, &M);
    }
    printf("C = %d; M = %d\n", C, M);
    return M + C;
}

void draw_table_heap(int *data, int n, int *teor_data) {
    printf("Трудоемкость построения пирамиды\n");
    printf("—————————————————————————————————————————————————\n");
    printf("| N\t| M + C teor\t| \tMf + Cf\t\t| \n");
    printf("|\t| \t\t| Убыв.\t| Случ.\t| Возр.\t|\n");
    printf("—————————————————————————————————————————————————\n");
    for (int s = 1; s <= 5; s++) {
        printf("| %d \t| %d\t\t|", s * 100, teor_data[s - 1]);
        for (int i = 0; i < 3; i++) {
            printf("%d\t| ", data[(s-1) * 3 + i]);
        }
        printf("\n");
    }
    printf("—————————————————————————————————————————————————\n\n");
}

void draw_table_sort(int *data, int n) {
    printf("Трудоемкость пирамидальной сортировки\n");
    printf("—————————————————————————————————\n");
    printf("| N\t| \tMf + Cf\t\t| \n");
    printf("|\t| Убыв.\t| Случ.\t| Возр.\t|\n");
    printf("—————————————————————————————————\n");
    for (int s = 1; s <= 5; s++) {
        printf("| %d \t|", s * 100);
        for (int i = 0; i < 3; i++) {
            printf("%d\t| ", data[(s-1) * 3 + i]);
        }
        printf("\n");
    }
    printf("—————————————————————————————————\n\n");
}