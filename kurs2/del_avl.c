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

void turn_LL(vertex** p) {
    vertex* q = (*p)->left;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->left = q->right;
    q->right = *p;
    *p = q;
}

void turn_LL1(vertex** p, int* umen) {
    vertex* q = (*p)->left;
    if (q->balance == 0) {
        q->balance = 1;
        (*p)->balance = -1;
        *umen = 0;
    } else {
        q->balance = 0;
        (*p)->balance = 0;
    }
    (*p)->left = q->right;
    q->right = *p;
    *p = q;
}

void turn_LR(vertex** p) {
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

void turn_RR(vertex** p) {
    vertex* q = (*p)->right;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->right = q->left;
    q->left = *p;
    *p = q;
}

void turn_RR1(vertex** p, int* umen) {
    vertex* q = (*p)->right;
    if (q->balance == 0) {
        q->balance = -1;
        (*p)->balance = 1;
        *umen = 0;
    } else {
        (*p)->balance = 0;
        q->balance = 0;
    }

    (*p)->right = q->left;
    q->left = *p;
    *p = q;
}

void turn_RL(vertex** p) {
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

void BL(vertex** p, int* umen) {
    if ((*p)->balance == -1) {
        (*p)->balance = 0;
    } else if ((*p)->balance == 0) {
        (*p)->balance = 1;
        *umen = 0;
    } else if ((*p)->balance == 1) {
        if ((*p)->right->balance >= 0) {
            turn_RR1(p, umen);
        } else {
            turn_RL(p);
        }
    }
}

void BR(vertex** p, int* umen) {
    if ((*p)->balance == 1) {
        (*p)->balance = 0;
    } else if ((*p)->balance == 0) {
        (*p)->balance = -1;
        *umen = 0;
    } else if ((*p)->balance == -1) {
        if ((*p)->left->balance <= 0) {
            turn_LL1(p, umen);
        } else {
            turn_LR(p);
        }
    }
}

void del(vertex** r, vertex** q, int* umen) {
    if ((*r)->right != NULL) {
        del(&((*r)->right), q, umen);
        if (*umen) {
            BR(r, umen);
        }
    } else {
        (*q)->data = (*r)->data;
        (*q) = (*r);
        (*r) = (*r)->left;
        *umen = 1;
    }
}

void delete_from_avl(int x, vertex** p, int* umen) {
    if ((*p) == NULL) {
    } else if (x < (*p)->data) {
        delete_from_avl(x, &((*p)->left), umen);
        if (*umen) {
            BL(p, umen);
        }
    } else if (x > (*p)->data) {
        delete_from_avl(x, &((*p)->right), umen);
        if (*umen) {
            BR(p, umen);
        }
    } else {
        vertex* q = *p;
        if (q->left == NULL) {
            *p = q->right;
            *umen = 1;
        } else if (q->right == NULL) {
            *p = q->left;
            *umen = 1;
        } else {
            del(&(q->left), &q, umen);
            if (*umen) {
                BL(p, umen);
            }
        }
        free(q);
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

void tree_is_avl(vertex* v, char* flag) {
    if (v == NULL || *flag) {
        return;
    }
    tree_is_avl(v->left, flag);
    tree_is_avl(v->right, flag);
    int height_diff = abs(height_of_tree(v->left) - height_of_tree(v->right));
    if (height_diff <= 1) {
    } else {
        *flag = 1;
    }
}

int main() {
    srand(time(NULL));
    int size = 12;
    int data[size];
    FillRand(data, size);
    printf("Создание АВЛ дерева поиска\n");
    vertex* root = NULL;
    int rost = 0;
    for (int i = 0; i < size; i++) {
        add_to_avl(data[i], &root, &rost);
    }
    int key = 0;
    int umen;
    obhod_left_right(root);
    printf("\n");
    do {
        char flag = 0;
        umen = 0;
        if (root != NULL)
            printf("Текущее значение корневой вершины: %d\n", root->data);
        else
            printf("В дереве не осталось элементов.\n");

        printf(
            "Введите ключ вершины для удаления (для выхода - отрицательное "
            "число): ");

        if (scanf("%d", &key)) {
            if (key >= 0) {
                int start_size = size_of_tree(root);
                delete_from_avl(key, &root, &umen);
                if (start_size != size_of_tree(root)) {
                    printf("\nЭлемент с ключом %d успешно удален из дерева.\n",
                           key);
                } else {
                    printf("\nЭлемент с ключом %d не найден в дереве.\n", key);
                }
                obhod_left_right(root);
                tree_is_avl(root, &flag);
                if (flag) {
                    printf("\nОшибка: дерево больше не АВЛ!\n");
                }
                printf("\nРазмер дерева - %d\n\n", size_of_tree(root));
            }
        } else {
            printf("Не удалось считать. Попробуйте еще раз.\n\n");
            while (getchar() != '\n');
        }
    } while (key >= 0);
    printf("Завершение программы.\n");
    delete_tree(root);
    return 0;
}