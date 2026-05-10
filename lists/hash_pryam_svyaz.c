#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct spis {
    struct spis *next;
    int data;
} spis;

const int primes[] = {11, 19, 31, 43, 53, 67, 79, 89, 97, 101};
int table_data[10];

void FillRandArray(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n * 2 + 1);
    }
}

int Hash(int x, int m) {
    return x % m;
}

int CalculateM(int n) {
    int m = (int)(n / (2.0 * log2(n)));
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

void AddToStack(spis **head, int data) {
    spis *p = malloc(sizeof(spis));
    p->data = data;
    p->next = *head;
    *head = p;
}

spis* FillDecS(int n) {
    spis *head = NULL;
    for (int i = 1; i <= n; i++) {
        AddToStack(&head, i);
    }
    return head;
}


spis* FillIncS(int n) {
    spis *head = NULL;
    for (int i = n; i >= 1; i--) {
        AddToStack(&head, i);
    }
    return head;
}

spis* FillRandS(int n) {
    spis *head = NULL;
    for (int i = 0; i <= n; i++) {
        AddToStack(&head, rand() % (10 * n + 1));
    }
    return head;
}

void AddToQueue(spis **tail, int data) {
    spis *p = malloc(sizeof(spis));
    p->data = data;
    p->next = NULL;
    (*tail)->next = p;
    *tail = p;
}

void FillIncQ(int n, spis **head, spis **tail) {
    (*tail) = (spis *)head;
    *head = NULL;
    for (int i = 1; i <= n; i++) {
        AddToQueue(tail, i);
    }
}

void FillDecQ(int n, spis **head, spis **tail) {
    (*tail) = (spis *)head;
    *head = NULL;
    for (int i = n; i > 0; i--) {
        AddToQueue(tail, i);
    }
}

void FillRandQ(int n, spis **head, spis **tail) {
    (*tail) = (spis *)head;
    *head = NULL;
    for (int i = 0; i < n; i++) {
        AddToQueue(tail, rand() % (2 * n + 1));
    }
}

void PrintSpis(spis *head) {
    if (head == NULL) return;
    spis *p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

int ControlSum(spis *head) {
    spis *p = head;
    int sum = 0;
    while (p != NULL) {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int RunNumber(spis *head) {
    spis *p = head;
    if (p == NULL) return 0; // Список пуст
    int num = 1;
    while (p->next != NULL) {
        if(p->data > p->next->data) num++;
        p = p->next;
    }
    return num;
}

void DeleteStack(spis **head) {
    if (head == NULL) return;
    spis *p = (*head);
    *head = NULL;
    spis *next;
    while (p->next != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
    free(p);
}

void DeleteQueue(spis **head, spis **tail) {
    if (head == NULL) return;
    spis *p = (*head);
    *head = NULL;
    *tail = NULL;
    spis *next;
    while (p->next != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
    free(p);
}

void PrincRecForward(spis *p) {
    if (p == NULL) return;
    printf("%d ", p->data);
    PrincRecForward(p->next);
}

void PrincRecReverse(spis *p) {
    if (p == NULL) return;
    PrincRecReverse(p->next);
    printf("%d ", p->data);
}

spis** CreateHashTable(int *data, int n, int *collisions) {
    int m = CalculateM(n);
    char is_added;
    spis** hash_table = (spis**)malloc(m * sizeof(spis*));
    for (int i = 0; i < m; i++) {
        hash_table[i] = FillIncS(0);
    }
    for (int i = 0; i < n; i++) {
        is_added = 0;
        int h = Hash(data[i], m);
        spis *p = hash_table[h];
        while (p != NULL) {
            if (p->data != data[i]) {
                (*collisions)++;
                p = p->next;
            } else {
                is_added = 1;
                break;
            }
        }
        if (!is_added) {
            AddToStack(&(hash_table[h]), data[i]);
        }
    }
    return hash_table;
}

spis** CreateHashTableFix(int *data, int n, int *collisions, int m) {
    char is_added;
    spis** hash_table = (spis**)malloc(m * sizeof(spis*));
    for (int i = 0; i < m; i++) {
        hash_table[i] = FillIncS(0);
    }
    for (int i = 0; i < n; i++) {
        is_added = 0;
        int h = Hash(data[i], m);
        spis *p = hash_table[h];
        while (p != NULL) {
            if (p->data != data[i]) {
                (*collisions)++;
                p = p->next;
            } else {
                is_added = 1;
                break;
            }
        }
        if (!is_added) {
            AddToStack(&(hash_table[h]), data[i]);
        }
    }
    return hash_table;
}

void Print_Hash_Table(spis **hash_table, int n) {
    int m = CalculateM(n);
    for (int i = 0; i < m; i++) {
        printf("%d: ", i);
        PrintSpis(hash_table[i]);
        printf("\n");
    }
}

int Search_Hash_Table(spis **hash_table, int m, int x, int *collisions, int *h) {
    *collisions = 0;
    *h = Hash(x, m);
    spis *p = hash_table[*h];
    int i = 0;
    while (p != NULL) {
        if (p->data == x) return i;
        else {
            (*collisions)++;
            p = p->next;
            i++;
        }
    }
    return -1;
}

void Hash_Testing(int n) {
    printf("Тест: построение хеш-таблицы для %d элементов входных данных\n", n);
    int A[n];
    FillRandArray(A, n);
    int collisions = 0;
    spis** hash_table;
    hash_table = CreateHashTable(A, n, &collisions);
    Print_Hash_Table(hash_table, n);
    printf("Число коллизий при создании таблицы - %d\n", collisions);
    printf("\nПоиск в таблице\n");
    int h = 0, m = CalculateM(n);
    int x = rand() % (n * 2 + 1);
    int i = Search_Hash_Table(hash_table, m, x, &collisions, &h);
    if (i == -1) printf("Элемент '%d' не найден\n", x);
    else printf("Элемент '%d' найден. Он находится в %d списке, индекс в списке - %d. Число коллизий при поиске - %d\n", x, h, i, collisions);
}

void Testing_For_Table(int i) {
    int n = 100;
    int A[n];
    FillRandArray(A, n);
    int collisions = 0;
    spis** hash_table;
    hash_table = CreateHashTableFix(A, n, &collisions, primes[i]);
    table_data[i] = collisions;
}

void Draw_Table() {
    printf("\nЗависимость количества коллизий от размера хеш-таблицы\n");
    printf("—————————————————————————————————————————————————————————————————————————————————\n");
    printf("| Размер хеш-таблицы\t| Количество исходных символов\t| Количество коллизий\t| \n");
    printf("—————————————————————————————————————————————————————————————————————————————————\n");
    for (int i = 0; i < 10; i++) {
        printf("|\t %d\t\t| \t\t%d\t\t| \t%d\t\t|\n", primes[i], 100, table_data[i]);
        printf("—————————————————————————————————————————————————————————————————————————————————\n");
    }
}

int main() {
    srand(time(NULL));
    Hash_Testing(100);
    for (int i = 0; i < 10; i++) {
        Testing_For_Table(i);
    }
    Draw_Table();
    return 0;
}   