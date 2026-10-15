#include <stdio.h>

int len(char* string) {
    int i = 0; 
    while (string[i] != '\0') i++;
    return i;
}

char substringCompare(char* string, char* substring, int s, int e, int *c) {
    for (int i = s; i <= e; i++) if (++(*c), string[i] != substring[i - s]) return 0;
    return 1;
}

int searchSubstring(char* string, char* substring) {
    int c = 0;
    int n = len(string), m = len(substring);
    int i = -1, j;
    do {
        i++;
        j = 0;
        while((j < m) && (++c, string[i + j] == substring[j])) j++;
        if ((j == m)) {
            printf("%d ", i);
        }
    } while (i < (n - m));
    printf("\n");
    return c;
}

int hash(char* string, int s, int e) {
    int h = 0;
    for (int i = s; i <= e; i++) h = (h * 256 + string[i]) % 13;
    return h;
}

int RabinKarp(char* string, char* substring) {
    int c = 0;
    int n = len(string), m = len(substring);
    int hash_string = hash(string, 0, m - 1);
    int hash_substring = hash(substring, 0, m - 1);
    for (int i = 0; i < n - m + 1; i++) {
        if (hash_string == hash_substring) if (substringCompare(string, substring, i, i + m - 1, &c)) printf("%d ", i);
        hash_string = hash(string, i + 1, i + m);
    } 
    printf("\n");
    return c;
}

int main() {
    char string[] = "70312345892461234505391712345846195";
    char substring_1[] = "12345";
    printf("====================================\n");
    printf("ТЕСТ 1 - Метод прямого поиска.\n");
    printf("Полная строка: '%s'.\nШаблон поиска: '%s'.\n", string, substring_1);
    printf("Первые вхождения шаблона в строку: ");
    int c1 = searchSubstring(string, substring_1);
    printf("Число посимвольных сравнений подстроки в ходе поиска = %d\n", c1);
    printf("====================================\n");
    printf("ТЕСТ 2 - Метод Рабина-Карпа.\n");
    printf("Полная строка: '%s'.\nШаблон поиска: '%s'.\n", string, substring_1);
    printf("Первые вхождения шаблона в строку: ");
    int c2 = RabinKarp(string, substring_1);
    printf("Число посимвольных сравнений подстроки в ходе поиска = %d\n", c2);
    printf("====================================\n");
    return 0;
}