#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void FillDec(int *A, int n);
void FillRand(int *A, int n);
int CheckSum(int *A, int n);
int RunNumber(int *A, int n);

#define MAX_NUM 101

int main() {
    srand(time(NULL));
    int n = 10;
    int A[n];
    
    printf("Возрастающий массив: \n");
    
    Fillinc(A, n);
    PrintMas(A, n);
    printf("Количество серий в массиве: %d\n", RunNumber(A, n));
    printf("Сумма элементов = %d \n\n", CheckSum(A, n));
    
    printf("Убывающий массив: \n");
    
    FillDec(A, n);
    PrintMas(A, n);
    printf("Количество серий в массиве: %d\n", RunNumber(A, n));
    printf("Сумма элементов = %d \n\n", CheckSum(A, n));

    printf("Случайный массив: \n");
    
    FillRand(A, n);
    PrintMas(A, n);
    printf("Количество серий в массиве: %d\n", RunNumber(A, n));
    printf("Сумма элементов = %d \n", CheckSum(A, n));

    printf("Случайный массив для эксперимента\n");
    
    int big[100];
    FillRand(big, 100);
    printf("Средняя длина серии = %.2f\n", (float)(sizeof(big) / sizeof(big[0])) / RunNumber(big, 100));

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
    for (int i = 0; i <= n; i++) {
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