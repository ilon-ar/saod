#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int test_num = 1;
int teor_data[5];
int data[15];

typedef struct spis {
    struct spis *next;
    int data;
} spis;

typedef struct queue {
    struct spis *head;
    struct spis *tail;
} queue;

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
    for (int i = 0; i < n; i++) {
        AddToStack(&head, rand() % (2 * n + 1));
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

void InitQueue(spis **head, spis **tail) {
    (*tail) = (spis *)head;
    *head = NULL;
}


void FillIncQ(int n, spis **head, spis **tail) {
    InitQueue(head, tail);
    for (int i = 1; i <= n; i++) {
        AddToQueue(tail, i);
    }
}

void FillDecQ(int n, spis **head, spis **tail) {
    InitQueue(head, tail);
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

void SplitList(spis *S, spis **a, spis **b, int n, int *M) {
    spis *k, *p;
    *a = S; *b = S->next; n = 1;
    k = *a; p = *b;
    while (p != NULL) {
        (*M)++;
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    if (k != NULL) k->next = NULL;
}

int LenOfSpis(spis *head) {
    int c = 0;
    spis *p = head;
    while (p != NULL) {
        c++;
        p = p->next;
    }
    return c;
}

void FromStackToQueue(spis **l_head, queue *q) {
    q->tail->next = *l_head;
    q->tail = *l_head;
    *l_head = (*l_head)->next;
    q->tail->next = NULL;
}

void MergeLists(spis **a, int *q, spis **b, int *r, queue *c, int *C, int *M) {
    int countA = *q, countB = *r;
    while (countA != 0 && countB != 0) {
        if (++(*C) && (*a)->data <= (*b)->data) {
            FromStackToQueue(a, c);
            countA--;
        } else {
            FromStackToQueue(b, c);
            countB--;
        }
        (*M)++;
    }
    while (countA > 0) {
        FromStackToQueue(a, c);
        countA--;
        (*M)++;
    }
    while (countB > 0) {
        FromStackToQueue(b, c);
        countB--;
        (*M)++;
    }
    *q = countA; *r = countB;
}

void MergeSort(spis **S, int n, int *C, int *M) {
    spis *a, *b;
    int q, r;
    SplitList(*S, &a, &b, n, M);
    int p = 1;
    queue c[2];
    while (p < n) {
        c[0].head = c[1].head = NULL;
        c[0].tail = (spis *)&(c[0].head);
        c[1].tail = (spis *)&(c[1].head);
        int i = 0, m = n;
        while (m > 0) {
            if (m >= p) q = p;
            else q = m;
            m -= q;
            if (m >= p) r = p; 
            else r = m;
            m -= r;
            MergeLists(&a, &q, &b, &r, &c[i], C, M);
            i = 1 - i;
        }
        a = c[0].head; b = c[1].head;
        p = 2 * p;
    }
    c[0].tail->next = NULL;
    *S = c[0].head;
}

void TestSplitList(int n) {
    printf("Разделение списков: \n");
    spis *S = FillIncS(n);
    printf("Изначальный список S: ");
    PrintSpis(S);
    printf("| %d элементов\n", LenOfSpis(S));    
    spis *a, *b;
    int M;
    SplitList(S, &a, &b, n, &M);
    printf("Список a: ");
    PrintSpis(a);
    printf("| %d элементов\n", LenOfSpis(a));
    printf("Список b: ");
    PrintSpis(b);
    printf("| %d элементов\n", LenOfSpis(b));
}

void TestMergeLists(int n) {
    printf("Слияние списков: \n");
    spis *S = FillIncS(n);
    int tmp;
    spis *a, *b;
    SplitList(S, &a, &b, n, &tmp);
    printf("Изначальные списки: \n");
    printf("Список a: ");
    PrintSpis(a);
    printf("| контрольная сумма = %d\nСписок b: ", ControlSum(a));
    PrintSpis(b);
    printf("| контрольная сумма = %d\n", ControlSum(b));
    int sum = ControlSum(a) + ControlSum(b);
    queue c;
    c.head = NULL;
    c.tail = (spis *)&(c.head);
    int C = 0, M = 0;
    int q = LenOfSpis(a), r = LenOfSpis(b);
    int teorC = q + r - 1, teorM = q + r;
    MergeLists(&a, &q, &b, &r, &c, &C, &M);
    printf("Очередь c (слияние a и b): "); 
    PrintSpis(c.head);
    printf("\nСумма до слияния: %d. После: %d.\nЧисло серий в слиянии: %d\n", sum, ControlSum(c.head), RunNumber(c.head));
    printf("Фактическая трудоемкость: %d сравнений, %d пересылок. Теоретическая: %d сравнений и %d пересылок\n", C, M, teorC, teorM);
}

void SortTesting(int n, int mode) {
    spis *S;
    printf("MergeSort. Тест %d: ", test_num);
    switch(mode) {
        case -1:
            printf("Обратно упорядоченный список ");
            S = FillDecS(n);
            break;
        case 0:
            printf("Случайный список ");
            S = FillRandS(n);
            break;
        case 1:
            printf("Упорядоченный список ");
            S = FillIncS(n);
            break;
        default:    
            printf("Неверный режим\n");
            return;
    }
    printf("длиной %d\n", n);
    int C = 0, M = 0;
    int controlSum = ControlSum(S);
    MergeSort(&S, n, &C, &M);
    int trud = C + M;
    int teor_trud = 2 * n * log2(n) + n;

    if ((controlSum == ControlSum(S)) && (RunNumber(S) == 1)) {
        printf("Список успешно отсортирован по возрастанию.\n");
    } else {
        printf("Список не удалось отсортировать. Контрольная сумма до = %d, после = %d. Количество серий = %d (должно быть %d).\n", controlSum, ControlSum(S), RunNumber(S), 1);
    }
    printf("Теоретическая трудоемкость = %d. Фактическая = %d.\n\n", teor_trud, trud);
    teor_data[n / 100 - 1] = teor_trud;
    data[test_num - 1] = trud;
    test_num++;
}

void DemonstrateSort() {
    printf("Демонстрация MergeSort. Случайный список из 10 элементов\n");
    spis *S = FillRandS(10);
    printf("Список до сортировки: ");
    PrintSpis(S);
    printf("\nСписок после сортировки: ");
    int C = 0, M = 0;
    MergeSort(&S, 10, &C, &M);
    PrintSpis(S);
}

void DrawTable() {
    printf("Трудоемкость сортировки прямого слияния\n");
    printf("————————————————————————————————————————————————\n");
    printf("| N\t| M + C теор\t| \t Mf + Cf\t| \n");
    printf("|\t| \t\t| Убыв.\t| Случ.\t| Возр.\t|\n");
    printf("————————————————————————————————————————————————\n");
    for (int i = 1; i <= 5; i++) {
        printf("| %d\t| %d\t\t| %d\t| %d\t| %d\t|\n", i * 100, teor_data[i - 1], data[(i - 1) * 3], data[(i - 1) * 3 + 1], data[(i - 1) * 3 + 2]);
    }
    printf("————————————————————————————————————————————————\n");
}

int main() {
    srand(time(NULL));
    TestSplitList(23);
    printf("========================\n");
    TestMergeLists(11);
    printf("========================\n");
    DemonstrateSort();
    printf("\n========================\n");
    for (int n = 100; n <= 500; n += 100) {
        for (int mode = -1; mode <= 1; mode++) {
            SortTesting(n, mode);
        }
    }
    
    DrawTable();
}   