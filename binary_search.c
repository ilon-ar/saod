#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void draw_table(int *data, int n);
int bin_search_v1(int *A, int n, int x, int *C);
int bin_search_v2(int *A, int n, int x, int *C);
void search_testing(int n, int version, int x);

int test_num =  1;
int table_data[20];

int main() {
    for (int i = 0; i < 20; i++) {
    }
    for (int n = 100; n < 1001; n += 100) {
        for (int v = 1; v <= 2; v++) {
            for (int i = -1; i < 2; i++) {
                int x;
                // sleep(1);
                
                switch (i) {
                    case -1:
                        x = 1;
                        break;
                    case 0:
                        x = n;
                        break;
                    case 1:
                        x = n + 1;
                        break;
                    default:
                        printf("OSHIBKA\n");
                        return 1;
                }
                // printf("%d %d %d\n", n, v, x);
                search_testing(n, v, x);
            }
        }
    }
    draw_table(table_data, 20);    
    return 0;   
}

void search_testing(int n, int version, int x) {
    printf("Тест %d. Размер массива %d, версия поиска %d\n", test_num, n, version);
    int A[n];
    Fillinc(A, n);
    int C, i;
    printf("Искомый элемент: %d\n", x);
    
    switch(version) {
        case 1:
            i = bin_search_v1(A, n, x, &C);
            break;
        case 2:
            i = bin_search_v2(A, n, x, &C);
            break;
        default:
            printf("Введена неверная версия поиска\n");
    }
    if (i == -1) printf("Элемент '%d' не найден.\n", x);
    else {
        printf("Элемент '%d' найден. Его индекс - [%d]\n", x, i);

    }
    printf("Поиск завершен. Колличество сравнений = %d\n\n", C);
    table_data[(test_num - 1) / 3] = C;
    test_num++;
}
int bin_search_v1(int *A, int n, int x, int *C) {
    int L = 0, R = n - 1;
    *C = 0;
    int m;
    while (L <= R) {
        m = (L + R) / 2;
        if (++(*C) && A[m] == x) return m;
        if (++(*C) && A[m] < x) L = m + 1;
        else R = m - 1;
    }
    return -1;
}

int bin_search_v2(int *A, int n, int x, int *C) {
    int L = 0, R = n - 1;
    *C = 0;
    int m;
    while (L < R) {
        m = (L + R) / 2;
        if (++(*C) && A[m] < x) L = m + 1;
        else R = m;
    }
    if (++(*C) && A[L] == x) return L;
    else return -1;
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


void draw_table(int *data, int n) {
    printf("-----------------------------------------\n");
    printf("| N\t|Cф (I версия)\t|Cф (II версия)\t|\n");
    printf("-----------------------------------------\n");
    int i = 0;
    for (int s = 1; s <= 10; s++) {
        printf("| %d\t| %d \t\t| %d\t\t|\n ",s * 100, data[i++], data[i++]);
        printf("----------------------------------------\n");
    }
}