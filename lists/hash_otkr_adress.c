#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct spis {
    struct spis *next;
    int data;
} spis;

const int primes[] = {59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
int table_data[20];

void FillRandArray(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n * 2 + 1) + 1;
    }
}

void PrintArray(int *A, int n) {for (int i = 0; i < n; i++) printf("%d ", A[i]);}


int HashLin(int x, int m, int i) {
    return (x % m + i) % m;
}

int HashKvad(int x, int m, int i) {
    return (x % m + i * i) % m;
}

int CalculateM(int n) {
    int m = n;
    char is_prime = 1;
    do {
        is_prime = 1;
        m++;
        if (m == 2 || m == 3) break;
        if (m % 2 == 0 || m % 3 == 0) is_prime = 0;
        else {
            for (int k = 5; k < (int)pow(m, 0.5); k++) {
                if (m % k == 0) {
                    is_prime = 0;
                    break;
                }
            }
        }
        
    } while (!is_prime);
    return m;
}

int* CreateHashTableLin(int *data, int n, int m, int *collision) {
    *collision = 0;
    int *hash_table = (int *)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) hash_table[i] = 0;
    for (int k = 0; k < n; k++) {
        int el = data[k];
        int i = 0;
        do {
            int j = HashLin(el, m, i);
            if (hash_table[j] == 0) {
                hash_table[j] = el;
                break;
            }
            (*collision)++;
            i++;
        } while (i != m);
    }
    return hash_table;
}

int SearchHashTableLin(int *hash_table, int m, int el, int *collision) {
    *collision = 0;
    int i = 0, j;
    do {
        int j = HashLin(el, m, i);
        if (hash_table[j] == el) return j;
        i++;
        (*collision)++;
    } while (hash_table[j] != 0 && i != m);
    return -1;
}

int* CreateHashTableKvad(int *data, int n, int m, int *collision) {
    *collision = 0;
    int *hash_table = (int *)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) hash_table[i] = 0;
    for (int k = 0; k < n; k++) {
        int el = data[k];
        int i = 0;
        do {
            int j = HashKvad(el, m, i);
            if (hash_table[j] == 0) {
                hash_table[j] = el;
                break;
            }
            (*collision)++;
            i++;
        } while (i != m);
        if (i == m) printf("Переполнение таблицы; Элемент %d был утерян.\n", el);
    }
    return hash_table;
}


int SearchHashTableKvad(int *hash_table, int m, int el, int *collision) {
    *collision = 0;
    int i = 0, j;
    do {
        int j = HashKvad(el, m, i);
        if (hash_table[j] == el) return j;
        i++;
        (*collision)++;
    } while (hash_table[j] != 0 && i != m);
    return -1;
}

void PrintHashTable(int *hash_table, int m) {
    printf("\nНомер ячейки\t");
    for (int i = 0; i < m; i++) printf("%5d", i);
    printf("\nСимвол\t\t");
    for (int i = 0; i < m; i++) {
        if (hash_table[i] == 0) printf("     ");
        else printf("%5d", hash_table[i]);
    }
    printf("\n");
}

void DemontrateHashTable(int n) {
    int data[n];
    FillRandArray(data, n);
    printf("Изначальный массив (%d элементов): ", n);
    PrintArray(data, n);
    printf("\n");
    int collision;
    int m = CalculateM(n);
    printf("========================================================================================");
    printf("\nХеш-таблица методом открытой адресации. Способ решения коллизий - линейные пробы.\n");
    int *hash_table;
    hash_table = CreateHashTableLin(data, n, m, &collision);
    PrintHashTable(hash_table, m);
    printf("Число коллизий при построении - %d\n", collision);
    int x = rand() % (n * 2 + 1) + 1;
    printf("Поиск в хеш-таблице. Ключ поиска - %d\n", x);
    int i = SearchHashTableLin(hash_table, m, x, &collision);
    if (i == -1) printf("Элемент не найден\n");
    else printf("Элемент найден. Его индекс - %d\n", i);
    printf("Число коллизий при поиске - %d\n", collision);
    printf("========================================================================================");
    printf("\nХеш-таблица методом открытой адресации. Способ решения коллизий - квадратичные пробы.\n");
    int *hash_table_kvad;
    hash_table_kvad = CreateHashTableKvad(data, n, m, &collision);
    PrintHashTable(hash_table_kvad, m);
    printf("Число коллизий при построении - %d\n", collision);
    x = rand() % (n * 2 + 1) + 1;
    printf("Поиск в хеш-таблице. Ключ поиска - %d\n", x);
    i = SearchHashTableKvad(hash_table, m, x, &collision);
    if (i == -1) printf("Элемент не найден\n");
    else printf("Элемент найден. Его индекс - %d\n", i);
    printf("Число коллизий при поиске - %d\n", collision);
    printf("========================================================================================\n");
}

void HashForTable() {
    for (int i = 0; i < 10; i++) {
        int m = primes[i];
        int n = 30;
        int A[n];
        FillRandArray(A, n);
        int collision;
        CreateHashTableLin(A, n, m, &collision);
        table_data[i * 2] = collision;
        CreateHashTableKvad(A, n, m, &collision);
        table_data[i * 2 + 1] = collision;
    }
}

void Draw_Table() {
    printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
    printf("| Размер хеш-таблицы\t| Количество исходных символов\t| Количество коллизий\t\t\t\t| \n");
    printf("|\t\t\t|\t\t\t\t| Линейные пробы \t| Квадратичные пробы\t|\n");
    printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
    for (int i = 0; i < 10; i++) {
        printf("|\t %d\t\t| \t\t%d\t\t| \t%d\t\t| \t%d\t\t|\n", primes[i], 30, table_data[2 * i], table_data[2 * i + 1]);
        printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
    }
}

int main() {
    srand(time(NULL));
    DemontrateHashTable(10);
    printf("\n\n");
    HashForTable();
    Draw_Table();
    return 0;
}   