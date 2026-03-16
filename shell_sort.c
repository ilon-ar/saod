#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void FillDec(int *A, int n);
void FillRand(int *A, int n);
int CheckSum(int *A, int n);
int RunNumber(int *A, int n);
void draw_table(int *data, int n);
void sort_testing(int n, int mode, int sort);
int insert_sort(int *A, int n);
int shell_sort(int *A, int n, int *h, int m);
void steps_knut(int *steps, int m);

int test_num = 1;
int table_data[10];


int main () {
    srand(time(NULL));
    sort_testing(100, 0, 1);
    sort_testing(100, 0, 0);
    sort_testing(200, 0, 1);
    sort_testing(200, 0, 0);
    sort_testing(300, 0, 1);
    sort_testing(300, 0, 0);
    sort_testing(400, 0, 1);
    sort_testing(400, 0, 0);
    sort_testing(500, 0, 1);
    sort_testing(500, 0, 0);

    
    draw_table(table_data, 10);
    return 0;
}

void sort_testing(int n, int mode, int sort) { //sort : 0 - shell, 1 - insert
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
    int m = (int)log2(n) - 1;
    int h[m];
    steps_knut(h, m);
    int controlsum = CheckSum(A, n);
    int trud;
    int teor_trud;
    switch(sort) {
        case 0: 
            printf("Shell Sort: ");
            teor_trud = (int)pow(n, 1.2);
            
            trud = shell_sort(A, n, h, m);
            break;
        case 1: 
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
    printf("\n");
    table_data[test_num - 1] = trud;
    test_num++;
}

void PrintMas(int *A, int n) {
    for (int i = 0; i < n; i++) {
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

void steps_knut(int* steps, int m) {
 steps[0] = 1;
 for (int i = 1; i < m; i++) {
  steps[i] = 2 * steps[i - 1] + 1;
  }
 }

int shell_sort(int *A, int n, int* h, int m) {
    int k, tmp, M = 0, C = 0;
    int j;
    for (m--; m >= 0; m--) { 
        k = h[m];
        for (int i = k; i < n; i++) {
            tmp = A[i]; M++;
            for (j = i - k; ++C &&  j >= 0 && tmp < A[j]; j -= k) {
                // ++C;
                A[j + k] = A[j]; M++;   
            }
            A[j + k] = tmp; M++;
        }
    }
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

void draw_table(int *data, int n){
    printf("-------------------------------------------------------------------------\n");
    printf("| N\t| Шаги по формуле Кнута\t\t| Insert\t | Shell\t|\n");
    printf("-------------------------------------------------------------------------\n");
    int i = 0; 
    for (int s = 1; s <= 5; s++) {
        printf("| %d\t| ", s * 100);
        int m = (int)log2(s * 100) - 1;
        int h[m];
        steps_knut(h, m);
        PrintMas(h, m);
        if (m == 8) {
            printf("\t|");
        } else if (m == 5) {
            printf("\t\t\t|");
        }
         else {
            printf("\t\t|");
        }
        for (; i < s * 2; i++) {
            printf(" %-6d\t|", data[i]);
        }
        printf("\n");
        printf("-------------------------------------------------------------------------\n");
    }

}