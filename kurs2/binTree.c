#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
} vertex;

// ВАРИАНТ 16

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
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

void obhod_top_bot(vertex* v) {  // ↓↓↓↓
    if (v == NULL) {
        return;
    }
    printf("%d ", v->data);
    obhod_top_bot(v->left);
    obhod_top_bot(v->right);
}

void obhod_bot_top(vertex* v) {  // ↑↑↑↑
    if (v == NULL) {
        return;
    }
    obhod_bot_top(v->left);
    obhod_bot_top(v->right);
    printf("%d ", v->data);
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

int main() {
    srand(time(NULL));
    vertex* root;
    // ПОСТРОЕНИЕ ДЕРЕВА
    root = (vertex*)malloc(sizeof(vertex));
    root->data = rand() % 10 + 11;
    root->left = (vertex*)malloc(sizeof(vertex));
    root->left->data = rand() % 10 + 11;
    root->left->right = (vertex*)malloc(sizeof(vertex));
    root->left->right->data = rand() % 10 + 11;
    root->left->left = (vertex*)malloc(sizeof(vertex));
    root->left->left->data = rand() % 10 + 11;
    root->left->left->right = (vertex*)malloc(sizeof(vertex));
    root->left->left->right->data = rand() % 10 + 11;
    root->left->left->right->right = (vertex*)malloc(sizeof(vertex));
    root->left->left->right->right->data = rand() % 10 + 11;

    // ОТРИСОВКА НА ЭКРАНЕ
    printf("       %d\n", root->data);
    printf("      /\n");
    printf("     %d\n", root->left->data);
    printf("    /  \\\n");
    printf("   %d   %d\n", root->left->left->data, root->left->right->data);
    printf("     \\\n");
    printf("      %d\n", root->left->left->right->data);
    printf("        \\\n");
    printf("         %d\n", root->left->left->right->right->data);
    // ОБХОД ДЕРЕВА
    printf("\nОбходы дерева\nСверху вниз: ");
    obhod_top_bot(root);
    printf("\nСлева направо: ");
    obhod_left_right(root);
    printf("\nСнизу вверх: ");
    obhod_bot_top(root);
    // ХАРАКТЕРИСТИКИ ДЕРЕВА
    printf("\n\nОсновные характеристики дерева\n");
    printf("Размер дерева: %d\n", size_of_tree(root));
    printf("Контрольная сумма: %d\n", control_sum(root));
    printf("Высота дерева: %d\n", height_of_tree(root));
    printf("Средняя высота дерева: %.2f\n", avg_height(root));
}