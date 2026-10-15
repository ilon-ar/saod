#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
    int balance;
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

void turn_LL(vertex **p) {
    vertex* q = (*p)->left;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->left = q->right;
    q->right = *p;
    *p = q;
}

void turn_LR(vertex **p) {
    vertex* q = (*p)->left;
    vertex* r = q->right;
    if (r->balance < 0) {
        (*p)->balance = 1;
    } else {
        (*p)->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1;
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    q->right = r->left;
    (*p)->left = r->right;
    r->left = q;
    r->right = *p;
    *p = r;
}

void turn_RR(vertex **p) {
    vertex* q = (*p)->right;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->right = q->left;
    q->left = *p;
    *p = q;
}

void turn_RL(vertex **p) {
    vertex* q = (*p)->right;
    vertex* r = q->left;
    if (r->balance > 0) {
        (*p)->balance = -1;
    } else {
        (*p)->balance = 0;
    }
    if (r->balance < 0) {
        q->balance = 1;
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    q->left = r->right;
    (*p)->right = r->left;
    r->left = *p;
    r->right = q;
    *p = r;
}

void add_to_avl(int data, vertex** p, int* rost) {
    if (*p == NULL) {
        *p = (vertex*)malloc(sizeof(vertex));
        (*p)->data = data;
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->balance = 0;
        *rost = 1;
    } else if ((*p)->data > data) {
        add_to_avl(data, &((*p)->left), rost);
        if (*rost) {
            if ((*p)->balance > 0) {
                (*p)->balance = 0;
                *rost = 0;
            } else if ((*p)->balance == 0) {
                (*p)->balance = -1;
                *rost = 1;
            } else {
                if ((*p)->left->balance < 0) {
                    turn_LL(p);
                    *rost = 0;
                } else {
                    turn_LR(p);
                    *rost = 0;
                }
            }
        }
    } else if ((*p)->data < data) {
        add_to_avl(data, &((*p)->right), rost);
        if (*rost) {
            if ((*p)->balance < 0) {
                (*p)->balance = 0;
                *rost = 0;
            } else if ((*p)->balance == 0) {
                (*p)->balance = 1;
                *rost = 1;
            } else {
                if ((*p)->right->balance > 0) {
                    turn_RR(p);
                    *rost = 0;
                } else {
                    turn_RL(p);
                    *rost = 0;
                }
            }
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

void draw_table(vertex* isdp, vertex* avl) {
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| n=100      | Размер | Контр. сумма | Высота | Средн.высота |\n");
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| ИСДП       | %6d | %12d | %6d | %12.2f |\n", size_of_tree(isdp),
           control_sum(isdp), height_of_tree(isdp), avg_height(isdp));
    printf("+------------+--------+--------------+--------+--------------+\n");
    printf("| АВЛ        | %6d | %12d | %6d | %12.2f |\n", size_of_tree(avl),
           control_sum(avl), height_of_tree(avl), avg_height(avl));
    printf("+------------+--------+--------------+--------+--------------+\n");
}

int main() {
    srand(time(NULL));
    int size = 100;
    int data[size];
    FillRand(data, size);
    printf("Создание АВЛ дерева поиска\n");
    vertex* root = NULL;
    int rost = 0;
    for (int i = 0; i < size; i++) {
        add_to_avl(data[i], &root, &rost);
    }
    printf("Обход слева направо: ");
    obhod_left_right(root);
    printf("\nХАРАКТЕРИСТИКИ АВЛ ДЕРЕВА ПОИСКА:\n");
    printf("Размер = %d\n", size_of_tree(root));
    printf("Контрольная сумма = %d\n", control_sum(root));
    printf("Высота = %d\n", height_of_tree(root));
    printf("Средняя высота = %.2f\n\n", avg_height(root));
    QuickSortV2(data, 0, size - 1);
    vertex* isdp = create_isdp(0, size - 1, data);
    printf("\t\t\tТаблица сравнения деревьев поиска \n");
    draw_table(isdp, root);
    delete_tree(isdp);
    delete_tree(root);
    return 0;
}