#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
} vertex;

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
        int isDuplicate;
        int candidate;
        do {
            isDuplicate = 0;
            candidate = rand() % (n * 10 + 1);
            for (int j = 0; j < i; j++) {
                if (A[j] == candidate) {
                    isDuplicate = 1; 
                    break;
                }
            }
        } while (isDuplicate);
        A[i] = candidate;
    }
}

void add_to_sdp(int data, vertex** root) {
    vertex** p = root;
    while (*p != NULL) {
        if (data < (*p)->data) {
            p = &((*p)->left);
        } else if (data > (*p)->data) {
            p = &((*p)->right);
        } else {
            printf("Вершина с данными %d уже есть в дереве.\n", data);
            break;
        }
    }
    if (*p == NULL) {
        *p = (vertex*)malloc(sizeof(vertex));
        (*p)->data = data;
        (*p)->left = NULL;
        (*p)->right = NULL;
    }
}

void add_rec_sdp(int data, vertex** p) {
    if ((*p) == NULL) {
        *p = (vertex*)malloc(sizeof(vertex));
        (*p)->data = data;
        (*p)->left = NULL;
        (*p)->right = NULL;
    } else if (data < (*p)->data) {
        add_rec_sdp(data, &((*p)->left));
    } else if (data > (*p)->data) {
        add_rec_sdp(data, &((*p)->right));
    } else {
        printf("Вершина с данными %d уже есть в дереве.\n", data);
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



void draw_table(vertex* isdp, vertex* sdp1, vertex* sdp2) {
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| n=100      | Размер | Контр. сумма | Высота | Средн.высота |\n");
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| ИСДП       | %6d | %12d | %6d | %12.2f |\n",
           size_of_tree(isdp), control_sum(isdp), height_of_tree(isdp),
           avg_height(isdp));
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| СДП1       | %6d | %12d | %6d | %12.2f |\n",
           size_of_tree(sdp1), control_sum(sdp1), height_of_tree(sdp1),
           avg_height(sdp1));
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| СДП2       | %6d | %12d | %6d | %12.2f |\n",
           size_of_tree(sdp2), control_sum(sdp2), height_of_tree(sdp2),
           avg_height(sdp2));
    printf("+------------+--------+--------------+--------+--------------+\n");
}

int main() {
    srand(time(NULL));
    int size = 100;
    int data[size];
    FillRand(data, size);
    printf(
        "Создание случайного дерева поиска (СДП) с помощью классической "
        "процедуры добавления\n");
    vertex* root = NULL;
    for (int i = 0; i < size; i++) {
        add_to_sdp(data[i], &root);
    }
    obhod_left_right(root);
    printf("\nХАРАКТЕРИСТИКИ СДП1:\n");
    printf("Размер СДП1 = %d\n", size_of_tree(root));
    printf("Контрольная сумма СДП1 = %d\n", control_sum(root));
    printf("Высота СДП1 = %d\n", height_of_tree(root));
    printf("Средняя высота СДП1 = %.2f\n", avg_height(root));
    printf("\n\n");
    printf(
        "Создание случайного дерева поиска (СДП) с помощью рекурсивной "
        "процедуры "
        "добавления\n");
    vertex* rec_root = NULL;
    for (int i = 0; i < size; i++) {
        add_rec_sdp(data[i], &rec_root);
    }
    obhod_left_right(rec_root);
    printf("\nХАРАКТЕРИСТИКИ СДП2(Рекурсивная процедура добавления):\n");
    printf("Размер СДП2 = %d\n", size_of_tree(rec_root));
    printf("Контрольная сумма СДП2 = %d\n", control_sum(rec_root));
    printf("Высота СДП2 = %d\n", height_of_tree(rec_root));
    printf("Средняя высота СДП2 = %.2f\n", avg_height(rec_root));
    printf("\n\n");
    QuickSortV2(data, 0, size - 1);
    vertex* isdp = create_isdp(0, size - 1, data);

    printf("\t\t\tТаблица сравнения деревьев поиска \n");
    draw_table(isdp, root, rec_root);

    delete_tree(root);
    delete_tree(rec_root);
    return 0;
}