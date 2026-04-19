#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct spis {
    struct spis *next;
    int data;
} spis;

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

int main() {
    srand(time(NULL));
    printf("\n—————————————————————————————————————————————————————————\n");
    printf("Фунции со стеком.\nТест 1: заполнение возрастающими + вывод.\n");
    spis *headS = FillIncS(20);
    PrintSpis(headS);
    printf("\n\nТест 2: удаление стека.\n");
    DeleteStack(&headS);
    printf("Голова пуста? %s", headS == 0 ? "да" : "нет");
    printf("\n\nТест 3: заполнение убывающими.\n");
    headS = FillDecS(20);
    PrintSpis(headS);
    DeleteStack(&headS);
    printf("\n\nТест 4: заполнение случайными.\n");
    headS = FillRandS(5);
    PrintSpis(headS);
    printf("\n\nТест 5: рекурсивный вывод.\nВ прямом порядке: ");
    PrincRecForward(headS);
    printf("\nВ обратном порядке: ");
    PrincRecReverse(headS);
    printf("\n\nТест 6: Подсчет контрольной суммы и количества серий.\n");
    printf("Контрольная сумма: %d; Количество серий: %d.\n", ControlSum(headS), RunNumber(headS));
    printf("\n—————————————————————————————————————————————————————————\n");
    printf("Функции с очередью.\nТест 1: заполнение возрастающими + вывод.\n");
    spis *headQ, *tailQ;
    FillIncQ(20, &headQ, &tailQ);
    PrintSpis(headQ);
    printf("\n\nТест 2: удаление очереди:\n");
    DeleteQueue(&headQ, &tailQ);
    printf("Голова пуста? %s. Хвост пуст? %s", headQ == 0 ? "да" : "нет", tailQ == 0? "да" : "нет");
    printf("\n\nТест 2: заполнение убывающими:\n");
    FillDecQ(20, &headQ, &tailQ);
    PrintSpis(headQ);
    DeleteQueue(&headQ, &tailQ);
    printf("\n\nТест 3: заполнение случайными:\n");
    FillRandQ(5, &headQ, &tailQ);
    PrintSpis(headQ);
    DeleteQueue(&headQ, &tailQ);
    printf("\n");
    return 0;
}   