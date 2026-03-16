#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define X(x) (1000 * (x - xmin)/(xmax - xmin) + 100)
#define Y(y) (900 - 1000 * (y - ymin)/(ymax - ymin))


int upgraded_select_sort(int *A, int n);
int bubble_sort(int *A, int n);
int shaker_sort(int *A, int n);
void FillRand(int *A, int n);
void PrintMas(int *A, int n);
int insert_sort(int *A, int n);
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
    outtext("T");
    setcolor(CYAN);

}
//gcc draw_graph.c -o draw $(pkg-config --cflags --libs cairo) -lgraphics -lm
int main() {
    
    srand(time(NULL));
    initgraph(1000, 1000, "graph");
    drawos();
    int k = 500;
    int graph_data_select[k];
    int graph_data_bubble[k];
    int graph_data_shaker[k];
    int graph_data_insert[k];
    int graph_data_shell[k];
    for (int i = 0; i < k; i++) {
        int ar[i];
        FillRand(ar, i);
        graph_data_select[i] = upgraded_select_sort(ar, i);
        FillRand(ar, i);
        graph_data_bubble[i] = bubble_sort(ar, i);
        FillRand(ar, i);
        graph_data_shaker[i] = shaker_sort(ar, i);
        FillRand(ar, i);
        graph_data_insert[i] = insert_sort(ar, i);
        int m = (int)log2(i + 1);
        int h[m];
        steps_knut(h, m);
        FillRand(ar, i);
        graph_data_shell[i] = shell_sort(ar, i, h, m);
    }
    
    // PrintMas(graph_data, k);
    float  y, ymin, ymax;
    int xmin = 0, xmax = k, x;
    

    ymax = graph_data_select[k - 1];
    ymin = graph_data_select[0];
    x = xmin, y = graph_data_select[0]; 
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setlinestyle(0, 1);
    setcolor(WHITE);
    printf("%d\n", k);
    setlinestyle(0, 3);
    setcolor(CYAN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    moveto(110, 910);
    outtext("Select Sort");
    setcolor(GREEN);
    moveto(300, 950);
    outtext("Shaker Sort");
    setcolor(YELLOW);
    moveto(300, 910);
    outtext("Bubble Sort");
    setcolor(RED);
    moveto(510, 910);
    outtext("Insert Sort");
    setcolor(MAGENTA);
    moveto(510, 950);
    outtext("Shell Sort");
    setcolor(CYAN);
    moveto(X(x), Y(y));
    for (x = xmin; x < 910; x++) {
        y = graph_data_select[x];
        lineto(X(x), Y(y));
        // delay(10);
    }

    x = xmin; y = graph_data_bubble[0];
    moveto(X(0), Y(0));

    setcolor(YELLOW);
    
    for (x = xmin; x < 650; x++) {
        y = graph_data_bubble[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    x = xmin; y = graph_data_bubble[0];
    moveto(X(0), Y(0));

    setcolor(GREEN);
    
    for (x = xmin; x < 1000; x++) {
        y = graph_data_shaker[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    x = xmin; y = graph_data_bubble[0];
    moveto(X(0), Y(0));

    setcolor(RED);
    
    for (x = xmin; x < 1000; x++) {
        y = graph_data_insert[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    x = xmin; y = graph_data_bubble[0];
    moveto(X(0), Y(0));

    setcolor(MAGENTA);
    
    for (x = xmin; x < 1000; x++) {
        y = graph_data_shell[x];

        lineto(X(x), Y(y));
        // delay(200);
    }


    while(true){};
    closegraph();
}
int upgraded_select_sort(int *A, int n) {
    int k; int tmp; int C = 0; int M = 0;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            C++;
            if (A[j] < A[k]) {
                k = j;
            }
        }
            tmp = A[i];
            A[i] = A[k];
            A[k] = tmp;
            M += 3;
        
    }
    return M + C;
}

int bubble_sort(int *A, int n){
    int M = 0;
    int C = 0;
    int tmp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            C++;
            if (A[j] < A[j-1]) {
                tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
                M += 3;
            }
        }
    }
    return M + C;
}
int shaker_sort(int *A, int n) {
    int M = 0, C = 0, L = 0, R = n, k = n, tmp;
    do {
        for (int j = R; j >= L + 1; j--) {
            C++;
            if (A[j] < A[j-1]) {
                M += 3;
                tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
                k = j;
            }
        }
        L = k;
        for (int j = L; j <= R - 1; j++) {
            C++;
            if (A[j] > A[j+1]) {
                M += 3;
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                k = j;
            }
        }
        R = k;
    } while (L < R);
    return M + C;
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
int insert_sort(int *A, int n) {
    int M = 0, C = 0, tmp, j;
    for (int i = 1; i < n; i++) {
        tmp = A[i]; M++;      
        for (j = i - 1; j >= 0 && tmp < A[j] && (C++ || 1); j--) {
            // C++;
            A[j + 1] = A[j]; M++;
        }
        // C++;
        A[j + 1] = tmp; M++;
    }
    return M + C;
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
            for (j = i - k; ++C && j >= 0 && tmp < A[j]; j -= k) {
                A[j + k] = A[j]; M++;   
            }
            A[j + k] = tmp; M++;
        }
    }
    return M + C;
}

