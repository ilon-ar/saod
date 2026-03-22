#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void Fillinc(int *A, int n);
void PrintMas(int *A, int n);
void draw_table(int *data, int n);
int bin_search_v1(int *A, int n, int x, int *C);
int bin_search_v2(int *A, int n, int x, int *C);
void search_testing(int n, int version, int x);

int test_num =  1;
int table_data[20];

int main() {
    srand(time(NULL));
    search_testing(100, 1, 3);
    search_testing(100, 2, 3);
    return 0;   
}

void search_testing(int n, int version, int x) {
    printf("Тест %d. Размер массива %d, версия поиска %d\n", test_num, n, version);
    int A[n];
    Fillinc(A, n);
    int C, i, n_x = 0;
    printf("Искомый элемент: %d\n", x);
    int first_i;
    
    switch(version) {
        case 1:
            i = bin_search_v1(A, n, x, &C);
            printf("%d\n", C);
            if(i != -1) {
                n_x++;
                int tmp = 1;
                while (++C && A[i - tmp]  == x && (i - tmp) >= 0) {
                    n_x++;
                    first_i = i - tmp++;
                }
                tmp = 1;

                while (++C && A[i + tmp] == x && (i + tmp++) < n) n_x++;
            }
            break;
        case 2:
            i = bin_search_v2(A, n, x, &C);
            if(i != -1) {
                first_i = i;
                n_x++;
                int tmp = 1;
                while (++C && A[i + tmp] == x && (i + tmp++) < n) n_x++;           
            }
            break;
        default:
            printf("Введена неверная версия поиска\n");
    }
    
    if (i == -1) printf("Элемент '%d' не найден.\n", x);
    else {
        int xis[n_x];
        for (int index = 0; index < n_x; index++) xis[index] = index + first_i;
        printf("Все элементы '%d' найдены. Их количество = %d; их индексы = ", x, n_x);
        PrintMas(xis, n_x);
        printf("\n");
    }
    PrintMas(A, n);
    printf("Поиск завершен. Колличество сравнений = %d\n\n", C);
    table_data[test_num - 1] = C;
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
    for (int i = 0; i < n; i++) {
        A[i] = i / 4 + 1;
    }   
}


void draw_table(int *data, int n) {
    printf("-----------------------------------------\n");
    printf("| N\t|Cф (I версия)\t|Cф (II версия)\t|\n");
    printf("-----------------------------------------\n");
    int i = 0;
    for (int s = 1; s <= 10; s++) {
        printf("| %d\t| %d \t\t| %d\t\t|\n ",s * 100, data[i], data[i + 1]);
        printf("----------------------------------------\n");
        i += 2;
    }
}