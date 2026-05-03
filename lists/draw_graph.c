#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define X(x) (1000 * (x - xmin)/(xmax - xmin) + 100)
#define Y(y) (900 - 1000 * (y - ymin)/(ymax - ymin))

typedef struct spis {
    struct spis *next;
    union {int data; unsigned char digit[4];};
} spis;

typedef struct queue {
    struct spis *head;
    struct spis *tail;
} queue;

char KDI4[] = {3, 2, 1, 0};

void PrintMas(int *A, int n);
void Fillinc(int *A, int n);
void FillRand(int *A, int n);
int AddToHeap(int *A, int n, int L, int R, int *C, int *M);
int HeapSort(int *A, int n);
void QuickSort(int *A, int n, int L, int R, int *C, int *M);
void MergeSort(spis **S, int n, int *C, int *M);
int DigitalSort4b(spis **S);
spis* FillRandS(int n);
void SplitList(spis *S, spis **a, spis **b, int n, int *M);
void FromStackToQueue(spis **l_head, queue *q);
void MergeLists(spis **a, int *q, spis **b, int *r, queue *c, int *C, int *M);
void AddToStack(spis **head, int data);




void drawos() {     //Отрисовка координатной оси
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setlinestyle(0, 1);
    line(0, 900, 1000, 900);
    moveto(950, 920);
    outtext("n");
    line(100, 0, 100, 1000);
    moveto(120, 20);
    outtext("C");
    setcolor(CYAN);

}
//gcc draw_graph.c -o draw $(pkg-config --cflags --libs cairo) -lgraphics -lm
int main() {
    
    srand(time(NULL));
    initgraph(1000, 1000, "graph");
    drawos();
    int k = 1000;
    int graph_data_heap[k];
    int graph_data_quick[k];
    int graph_data_merge[k];
    int graph_data_digital[k];
    
    for (int i = 0; i < k + 1; i++) {
        int ar[i];
        
        FillRand(ar, i);
        graph_data_heap[i] = HeapSort(ar, i);
        FillRand(ar, i);
        int C = 0, M = 0;
        QuickSort(ar, i, 0, i - 1, &C, &M);
        graph_data_quick[i] = C + M;
        spis *S = FillRandS(i);
        C = 0; M = 0;
        MergeSort(&S, i, &C, &M);
        graph_data_merge[i] = C + M;
        graph_data_digital[i] = DigitalSort4b(&S);
    }
    graph_data_heap[0] = 0;
    graph_data_merge[0] = 0;
    graph_data_quick[0] = 0;
    // PrintMas(graph_data_1, k);
    // PrintMas(graph_data_2, k);
    
    // PrintMas(graph_data, k);
    float  y, ymin, ymax;
    int xmin = 0, xmax = k , x;
    
    ymax = graph_data_heap[k - 1];
    ymin = 0;
    x = xmin, y = graph_data_heap[0]; 
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setlinestyle(0, 2);
    setcolor(WHITE);
    printf("%d\n", k);
    setlinestyle(0, 2);
    setcolor(CYAN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    moveto(110, 910);
    outtext("Digital Sort");
    setcolor(GREEN);
    moveto(350, 910);
    outtext("Heap Sort");
    setcolor(RED);
    moveto(490, 910);
    outtext("Quick Sort");
    setcolor(YELLOW);
    moveto(650, 910);
    outtext("Merge Sort");

    
    x = xmin; y = graph_data_heap[0];
    moveto(X(x), Y(y));

    setcolor(GREEN);
    for (x = xmin; x < xmax; x++) {
        y = graph_data_heap[x];
        lineto(X(x), Y(y));
        // delay(200);
    }

    x = xmin; y = graph_data_quick[0];
    moveto(X(x), Y(y));
    setcolor(RED);
    for (x = xmin; x < xmax; x++) {
        y = graph_data_quick[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    x = xmin; y = graph_data_merge[0];
    moveto(X(x), Y(y));
    setcolor(YELLOW);
    for (x = xmin; x < xmax; x++) {
        y = graph_data_merge[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    x = xmin; y = graph_data_digital[0];
    moveto(X(x), Y(y));
    setcolor(CYAN);
    for (x = xmin; x < xmax; x++) {
        y = graph_data_digital[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    while(true){};
    closegraph();
}
void FillRand(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n * 2 + 1);
    }
}
void AddToStack(spis **head, int data) {
    spis *p = malloc(sizeof(spis));
    p->data = data;
    p->next = *head;
    *head = p;
}
spis* FillRandS(int n) {
    spis *head = NULL;
    for (int i = 0; i < n; i++) {
        AddToStack(&head, rand() % (2 * n + 1));
    }
    return head;
}
void PrintMas(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
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
    if (n < 2) return;
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
    (*M) *= 1.5;
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
    return M + C;
}

void QuickSort(int *A, int n, int L, int R, int *C, int *M) {
    (*M)++;
    int x = A[L], i = L, j = R, tmp;
    while (i <= j) {
        while (++(*C) && A[i] < x) i++;
        while (++(*C) && A[j] > x) j--;
        if (i <= j) {
            *M += 3;
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            i++; j--;
        }
    }
    if (L < j) QuickSort(A, n, L, j, C, M);
    if (i < R) QuickSort(A, n, i, R, C, M);
}

void Fillinc(int *A, int n) {
    for (int i = 1; i <= n; i++) {
        A[i - 1] = i;
    }   
}