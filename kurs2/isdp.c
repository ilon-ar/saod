#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
} vertex;

void obhod_left_right(vertex* v) {  // >>>>
    if (v == NULL) {
        return;
    }
    obhod_left_right(v->left);
    printf("%d ", v->data);
    obhod_left_right(v->right);
}

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int size_of_tree(vertex* v) {
    if (v == NULL) {
        return 0;
    }
    return 1 + size_of_tree(v->left) + size_of_tree(v->right);
}

int control_sum(vertex* v) {
    if (v == NULL) {
        return 0;
    }
    return v->data + control_sum(v->left) + control_sum(v->right);
}

int height_of_tree(vertex* v) {
    if (v == NULL) {
        return 0;
    }
    return 1 + max(height_of_tree(v->left), height_of_tree(v->right));
}

int path_length_sum(vertex* v, int l) {
    if (v == NULL) {
        return 0;
    }
    return l + path_length_sum(v->left, l + 1) +
           path_length_sum(v->right, l + 1);
}

float avg_height(vertex* v) {
    return (float)path_length_sum(v, 1) / size_of_tree(v);
}

void FillRand(int* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n * 2 + 1);
    }
}

void QuickSortV2(int* A, int L, int R) {
    while (L < R) {
        int x = A[L], i = L, j = R, tmp;

        while (i <= j) {
            while (A[i] < x) i++;
            while (A[j] > x) j--;
            if (i <= j) {
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
                i++;
                j--;
            }
        }

        if (j - L < R - i) {
            QuickSortV2(A, L, j);
            L = i;
        } else {
            QuickSortV2(A, i, R);
            R = j;
        }
    }
}

vertex* create_isdp(int L, int R, int* data) {
    if (L > R) {
        return NULL;
    }
    int m = (float)(L + R + 1) / 2;
    vertex* p = (vertex*)malloc(sizeof(vertex));
    p->data = data[m];
    p->left = create_isdp(L, m - 1, data);
    p->right = create_isdp(m + 1, R, data);
    return p;
}

void delete_tree(vertex* v) {
    if (v == NULL) {
        return;
    }
    delete_tree(v->left);
    delete_tree(v->right);
    free(v);
}

int main() {
    srand(time(NULL));
    int size = 100;
    int data[size];
    FillRand(data, size);
    QuickSortV2(data, 0, size - 1);
    vertex* root = create_isdp(0, size - 1, data);
    printf(
        "Создано Идеально Сбалансированное Дерево Поиска (ИСДП) из %d "
        "элементов.\n"
        "Обход слева-направо: ",
        size);
    obhod_left_right(root);
    printf("\n\nХАРАКТЕРИСТИКИ ПОСТРОЕННОГО ДЕРЕВА:\n");
    printf("Размер ИСДП = %d\n", size_of_tree(root));
    printf("Контрольная сумма ИСДП = %d\n", control_sum(root));
    printf("Высота ИСДП = %d\n", height_of_tree(root));
    printf("Средняя высота ИСДП = %.2f\n", avg_height(root));
    delete_tree(root);
    return 0;
}