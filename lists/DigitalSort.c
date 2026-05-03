#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int test_num = 1;
int teor_data[5];
int data[15];
char KDI4[] = {3, 2, 1, 0};
char KDI2[] = {1, 0};

typedef struct spis {
    struct spis *next;
    union {int data; unsigned char digit[4];};
} spis;

typedef struct spis2b {
    struct spis2b *next;
    union {short data; unsigned char digit[2];};
} spis2b;

typedef struct spisSurname {
    struct spisSurname *next;
    char data[40];
} spisSurname;

typedef struct queue {
    struct spis *head;
    struct spis *tail;
} queue;

typedef struct queue2b {
    struct spis2b *head;
    struct spis2b *tail;
} queue2b;

typedef struct queueSurname {
    struct spisSurname *head;
    struct spisSurname *tail;
} queueSurname;

void AddToStack2b(spis2b **head, short data) {
    spis2b *p = malloc(sizeof(spis2b));
    p->data = data;
    p->next = *head;
    *head = p;
}   

void AddToStack(spis **head, int data) {
    spis *p = malloc(sizeof(spis));
    p->data = data;
    p->next = *head;
    *head = p;
}   

void AddToStackSurname(spisSurname **head, char* data) {
    spisSurname *p = malloc(sizeof(spisSurname));
    strcpy(p->data, data);
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

spis* FillRandS4(int n) {
    spis *head = NULL;
    for (int i = 0; i < n; i++) {
        AddToStack(&head, rand() % (10000));
    }
    return head;
}

spis2b* FillRandS2(int n) {
    spis2b *head = NULL;
    for (int i = 0; i < n; i++) {
        AddToStack2b(&head, rand() % (1000));
    }
    return head;
}

spisSurname* FillSSurname(int n, char surnames[][40]) {
    spisSurname *head = NULL;
    for (int i = 0; i < n; i++) {
        AddToStackSurname(&head, surnames[i]);
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

void PrintSpis2(spis2b *head) {
    if (head == NULL) return;
    spis2b *p = head;
    while (p != NULL) {
        printf("%hd ", p->data);
        p = p->next;
    }
}

void PrintSpisSurname(spisSurname *head) {
    if (head == NULL) return;
    spisSurname *p = head;
    while (p != NULL) {
        printf("%s ", p->data);
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

int DigitalSort4b(spis **S) {
    int M = 0;
    for (int j = 3; j >= 0; j--) {
        queue Q[256];
        for (int i = 0; i < 256; i++) {
            Q[i].tail = (spis *)&(Q[i].head);
            Q[i].head = NULL;
        } 
        spis *p = *S;
        char k = KDI4[j];
        while (p != NULL) {
            unsigned char d = p->digit[k];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
            M++;
        }

        spis tmp;
        p = &tmp;
        for (int i = 0; i < 256; i++) {
            if (Q[i].tail != (spis *)&(Q[i].head)) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        *S = tmp.next;
    }
    return M;
}

int DigitalSortSurname(spisSurname **S) {
    int M = 0;
    for (int j = 3; j >= 0; j--) {
        queueSurname Q[256];
        for (int i = 0; i < 256; i++) {
            Q[i].tail = (spisSurname *)&(Q[i].head);
            Q[i].head = NULL;
        } 
        spisSurname *p = *S;
        while (p != NULL) {
            unsigned char d = p->data[j];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
            M++;
        }

        spisSurname tmp;
        p = &tmp;
        for (int i = 0; i < 256; i++) {
            if (Q[i].tail != (spisSurname *)&(Q[i].head)) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        *S = tmp.next;
    }
    return M;
}

int DigitalSortSurnameReversed(spisSurname **S) {
    int M = 0;
    for (int j = 3; j >= 0; j--) {
        queueSurname Q[256];
        for (int i = 0; i < 256; i++) {
            Q[i].tail = (spisSurname *)&(Q[i].head);
            Q[i].head = NULL;
        } 
        spisSurname *p = *S;
        while (p != NULL) {
            unsigned char d = p->data[j];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
            M++;
        }

        spisSurname tmp;
        p = &tmp;
        for (int i = 255; i >= 0; i--) {
            if (Q[i].tail != (spisSurname *)&(Q[i].head)) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        *S = tmp.next;
    }
    return M;
}

int DigitalSort4bReversed(spis **S) {
    int M = 0;
    for (int j = 3; j >= 0; j--) {
        queue Q[256];
        for (int i = 0; i < 256; i++) {
            Q[i].tail = (spis *)&(Q[i].head);
            Q[i].head = NULL;
        } 
        spis *p = *S;
        char k = KDI4[j];
        while (p != NULL) {
            unsigned char d = p->digit[k];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
            M++;
        }

        spis tmp;
        p = &tmp;
        for (int i = 255; i >= 0; i--) {
            if (Q[i].tail != (spis *)&(Q[i].head)) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        *S = tmp.next;
    }
    return M;
}

int DigitalSort2b(spis2b **S) {
    int M = 0;
    for (int j = 1; j >= 0; j--) {
        queue2b Q[256];
        for (int i = 0; i < 256; i++) {
            Q[i].tail = (spis2b *)&(Q[i].head);
            Q[i].head = NULL;
        } 
        spis2b *p = *S;
        char k = KDI2[j];
        while (p != NULL) {
            unsigned char d = p->digit[k];
            Q[d].tail->next = p;
            Q[d].tail = p;
            p = p->next;
            M++;
        }

        spis2b tmp;
        p = &tmp;
        for (int i = 0; i < 256; i++) {
            if (Q[i].tail != (spis2b *)&(Q[i].head)) {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        *S = tmp.next;
    }
    return M;
}

void SortTesting(int n, int mode) {
    spis *S;
    printf("DigitalSort. Тест %d: ", test_num);
    switch(mode) {
        case -1:
            printf("Обратно упорядоченный список ");
            S = FillDecS(n);
            break;
        case 0:
            printf("Случайный список ");
            S = FillRandS4(n);
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
    int controlSum = ControlSum(S);
    int trud = DigitalSort4b(&S);
    int teor_trud = 4 * n;

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
    printf("Демонстрация DigitalSort для 4 байтового числа. Случайный список из 10 элементов\n");
    spis *S = FillRandS4(10);
    printf("Список до сортировки: ");
    PrintSpis(S);
    int trud = DigitalSort4b(&S);
    printf("\nСписок после сортировки: ");
    PrintSpis(S);
    printf("\nКоличество пересылок = %d. Теоретическое значение = %d\n", trud, 4 * 10);
    printf("Список в обратном порядке: ");
    DigitalSort4bReversed(&S);
    PrintSpis(S);
    printf("\n\nДемонстрация DigitalSort для 2 байтового числа. Случайный список из 10 элементов\n");
    spis2b *S2 = FillRandS2(10);
    printf("Список до сортировки: ");
    PrintSpis2(S2);
    trud = DigitalSort2b(&S2);
    printf("\nСписок после сортировки: ");
    PrintSpis2(S2);
    printf("\nКоличество пересылок = %d. Теоретическое значение = %d\n", trud, 2 * 10);


}

void DrawTable() {
    printf("Трудоемкость цифровой сортировки DigitalSort\n");
    printf("————————————————————————————————————————————————\n");
    printf("| N\t| Mтеор\t\t| \t Mf\t\t| \n");
    printf("|\t| \t\t| Убыв.\t| Случ.\t| Возр.\t|\n");
    printf("————————————————————————————————————————————————\n");
    for (int i = 1; i <= 5; i++) {
        printf("| %d\t| %d\t\t| %d\t| %d\t| %d\t|\n", i * 100, teor_data[i - 1], data[(i - 1) * 3], data[(i - 1) * 3 + 1], data[(i - 1) * 3 + 2]);
    }
    printf("————————————————————————————————————————————————\n");
}

int main() {
    srand(time(NULL));
    DemonstrateSort();
    for (int n = 100; n <= 500; n += 100) {
        for (int mode = -1; mode <= 1; mode++) {
            SortTesting(n, mode);
        }
    }
    DrawTable();    
    printf("\nЦифровая сортировка списка фамилий: \n");
    char surnames[10][40] = {
        "Ivanov",
        "Petrov",
        "Sidorov",
        "Kuznetsov",
        "Smirnov",
        "Popov",
        "Vasiliev",
        "Sokolov",
        "Mikhailov",
        "Fedorov"
    };
    spisSurname *S = FillSSurname(10, surnames);
    printf("Список до сортировки: ");
    PrintSpisSurname(S);
    DigitalSortSurname(&S);
    printf("\nСписок после сортировки: ");
    PrintSpisSurname(S);
    printf("\nСписок в обратном порядке: ");
    DigitalSortSurnameReversed(&S);
    PrintSpisSurname(S);
}   