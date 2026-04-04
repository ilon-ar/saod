#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define X(x) (1000 * (x - xmin)/(xmax - xmin) + 100)
#define Y(y) (900 - 1000 * (y - ymin)/(ymax - ymin))



void PrintMas(int *A, int n);
void Fillinc(int *A, int n);
void FillRand(int *A, int n);
int AddToHeap(int *A, int n, int L, int R, int *C, int *M);
int HeapSort(int *A, int n);
int shell_sort(int *A, int n, int *h, int m);
void steps_knut(int *steps, int m);



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
    int graph_data_shell[k];
    int graph_data_heap[k];
    
    for (int i = 0; i < k + 1; i++) {
        int ar[i];
        int m = (int)log2(i + 1);
        int h[m];
        steps_knut(h, m);
        FillRand(ar, i);
        graph_data_shell[i] = shell_sort(ar, i, h, m);
        FillRand(ar, i);
        graph_data_heap[i] = HeapSort(ar, i);
        
    }
    // PrintMas(graph_data_1, k);
    // PrintMas(graph_data_2, k);
    
    // PrintMas(graph_data, k);
    float  y, ymin, ymax;
    int xmin = 0, xmax = k , x;
    
    ymax = graph_data_shell[k - 1] * 1.5;
    ymin = 0;
    x = xmin, y = graph_data_shell[0]; 
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setlinestyle(0, 2);
    setcolor(WHITE);
    printf("%d\n", k);
    setlinestyle(0, 2);
    setcolor(CYAN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    moveto(110, 910);
    outtext("Shell Sort");
    setcolor(GREEN);
    moveto(350, 910);
    outtext("Heap Sort");
    
    setcolor(CYAN);
    moveto(X(0), Y(0));
    graph_data_shell[0] = 0;
    for (x = xmin; x < xmax; x++) {
        y = graph_data_shell[x];
        lineto(X(x), Y(y));
        // delay(10);
    }

    x = xmin; y = graph_data_heap[0];
    moveto(X(x), Y(y));

    setcolor(GREEN);
    
    for (x = xmin; x < xmax; x++) {
        y = graph_data_heap[x];

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
void PrintMas(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
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
    return M + C;
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

void Fillinc(int *A, int n) {
    for (int i = 1; i <= n; i++) {
        A[i - 1] = i;
    }   
}