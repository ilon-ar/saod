#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define X(x) (1000 * (x - xmin)/(xmax - xmin) + 100)
#define Y(y) (900 - 1000 * (y - ymin)/(ymax - ymin))



void PrintMas(int *A, int n);
void Fillinc(int *A, int n);
int bin_search_v1(int *A, int n, int x, int *C);
int bin_search_v2(int *A, int n, int x, int *C);



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
    int graph_data_1[k];
    int graph_data_2[k];
    
    for (int i = 1; i < k + 1; i++) {
        int ar[i * 100];
        int C = 0;
        Fillinc(ar, i * 100);
        int x = rand() % i * 100 + 1;
        bin_search_v1(ar, i * 100, x, &C);
        graph_data_1[i - 1] = C;
        bin_search_v2(ar, i * 100, x, &C);
        graph_data_2[i - 1] = C;
    }
    // PrintMas(graph_data_1, k);
    // PrintMas(graph_data_2, k);
    
    // PrintMas(graph_data, k);
    float  y, ymin, ymax;
    int xmin = 0, xmax = k , x;
    
    ymax = graph_data_1[k - 1] * 1.5;
    ymin = 0;
    x = xmin, y = graph_data_1[0]; 
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setlinestyle(0, 1);
    setcolor(WHITE);
    printf("%d\n", k);
    setlinestyle(0, 3);
    setcolor(CYAN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    moveto(110, 910);
    outtext("Binary Search V1");
    setcolor(GREEN);
    moveto(350, 910);
    outtext("Binary Search V2");
    
    setcolor(CYAN);
    moveto(X(x), Y(y));
    for (x = xmin; x < xmax; x++) {
        y = graph_data_1[x];
        lineto(X(x), Y(y));
        // delay(10);
    }

    x = xmin; y = graph_data_2[0];
    moveto(X(x), Y(y));

    setcolor(GREEN);
    
    for (x = xmin; x < xmax; x++) {
        y = graph_data_2[x];

        lineto(X(x), Y(y));
        // delay(200);
    }

    
    while(true){};
    closegraph();
}
void PrintMas(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
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
void Fillinc(int *A, int n) {
    for (int i = 1; i <= n; i++) {
        A[i - 1] = i;
    }   
}