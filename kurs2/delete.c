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

int size_of_tree(vertex* v) {
    if (v == NULL) {
        return 0;
    }
    return 1 + size_of_tree(v->left) + size_of_tree(v->right);
}


void fill_rand(int* A, int n) {
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

char delete_from_sdp(int data, vertex** root) {
    vertex** p = root;
    while (*p != NULL) {
        if (data < (*p)->data) {
            p = &((*p)->left);
        } else if (data > (*p)->data) {
            p = &((*p)->right);
        } else {
            break;
        }
    }
    if (*p != NULL) {
        vertex* q = *p;
        if (q->left == NULL) {
            *p = q->right;
        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            vertex* r = q->left;
            if (r->right == NULL) {
                r->right = q->right;
                *p = r;
            } else {
                vertex* s = q;
                while (r->right != NULL) {
                    s = r;
                    r = r->right;
                }
                s->right = r->left;
                r->left = q->left;
                r->right = q->right;
                *p = r;
            }
        }
        free(q);
        return 1;
    }
    return 0;
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
    int size = 12;
    int data[size];
    fill_rand(data, size);
    printf("Создание случайного дерева поиска (СДП)\n");
    vertex* root = NULL;
    for (int i = 0; i < size; i++) {
        add_to_sdp(data[i], &root);
    }
    printf("\nИзначальный вид дерева:\n");
    obhod_left_right(root);
    printf("\nРазмер дерева - %d\n\n", size_of_tree(root));
    printf("\n");

    int key = 0;
    do {
        if (root != NULL) printf("Текущее значение корневой вершины: %d\n", root->data);
        else printf("В дереве не осталось элементов.\n");

        printf(
            "Введите ключ вершины для удаления (для выхода - отрицательное "
            "число): ");

        if (scanf("%d", &key)) {
            if (key >= 0) {
                if (delete_from_sdp(key, &root)) {
                    printf("\nЭлемент с ключом %d успешно удален из дерева.\n",
                           key);
                } else {
                    printf("\nЭлемент с ключом %d не найден в дереве.\n", key);
                }
                obhod_left_right(root);
                printf("\nРазмер дерева - %d\n\n", size_of_tree(root));
                
            }
        } else {
            printf("Не удалось считать. Попробуйте еще раз.\n\n");
            while (getchar() != '\n');
        }
    } while (key >= 0);
    printf("Завершение программы.\n");
    delete_tree(root);
    printf("\n");
    return 0;
}