#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct 
{
    long number;
    char name[100];
    char surname[100];
    char adress[100];
} Phone_t;

char PhoneIsLess(Phone_t phone1, Phone_t phone2) {
    if (strcmp(phone1.name, phone2.name) < 0) {
        return 1;
    } else if (strcmp(phone1.name, phone2.name) == 0 && strcmp(phone1.surname, phone2.surname) < 0) {
        return 1;
    } else return 0;
}

void SortPhonesByName(Phone_t *phones, int n, int *index) { // select
    int k;
    int tmp;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            if (PhoneIsLess(phones[index[j]], phones[index[k]])) {
                k = j;
            }
        }
        tmp = index[i];
        index[i] = index[k];
        index[k] = tmp;
    }
}

void SortPhonesByNumber(Phone_t *phones, int n, int *index) { // select
    int k;
    int tmp;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            if (phones[index[j]].number < phones[index[k]].number) {
                k = j;
            }
        }
        tmp = index[i];
        index[i] = index[k];
        index[k] = tmp;
    }
}



void PrintPhone(Phone_t phone){
    printf("\n-------------------\n");
    printf("number: %ld \n", phone.number);
    printf("abonent: %s %s \n", phone.name, phone.surname);
    printf("adress: %s\n", phone.adress);
    printf("-------------------\n");
}
void PhoneContructor(Phone_t *phone, long number, char *name, char *surname, char *adress) {
    phone->number = number;
    snprintf(phone->name, sizeof(phone->name), "%s", name);
    snprintf(phone->surname, sizeof(phone->surname), "%s", surname);
    snprintf(phone->adress, sizeof(phone->adress), "%s", adress);
}

int BinarySearchByName(Phone_t *phones, int n, char *name, int *index) {
    int L = 0, R = n - 1;
    int m;
    while(L < R) {
        m = (L + R) / 2;
        if (strcmp(phones[index[m]].name, name) < 0) L = m + 1;
        else R = m;
    }
    if (strcmp(phones[index[L]].name, name) == 0) return L;
    else return -1;
}

int BinarySearchByNumber(Phone_t *phones, int n, long number, int *index) {
    int L = 0, R = n - 1;
    int m;
    while(L < R) {
        m = (L + R) / 2;
        if (phones[index[m]].number < number) L = m + 1;
        else R = m;
    }
    if (phones[index[L]].number == number) return L;
    else return -1;
}

int main() {
    Phone_t John, Alex, Bob, Dan;
    PhoneContructor(&John, 223455, "John", "Penguin", "Pushkina 40");
    PhoneContructor(&Alex, 123456, "Alex", "Lion", "Pokrishkina 21");
    PhoneContructor(&Bob, 654321, "Bob", "Cast", "Asfaltnaya 42");
    PhoneContructor(&Dan, 890123, "Dan", "Frag", "Lenina 67");
    Phone_t phones[4] = {John, Alex, Bob, Dan};
    int index1[4], index2[4];
    printf("Неотсортированный массив структур: ");
    for (int i = 0; i < 4; i++)  {
        index1[i] = i;
        index2[i] = i;
        PrintPhone(phones[i]);
    }
    SortPhonesByName(phones, 4, index1);
    printf("\nМассив структур после сортировки (сортировка по имени/фамилии абонента): ");
    for (int i = 0; i < 4; i++)  {
        PrintPhone(phones[index1[i]]);
    }
    SortPhonesByNumber(phones, 4, index2);
    printf("Массив структур после сортировки (сортировка по номеру телефона): ");
    for (int i = 0; i < 4; i++)  {
        PrintPhone(phones[index2[i]]);
    }
    printf("\nДвоичный поиск по имени:\n");
    char searching_name[100] = "Alex";
    int i = BinarySearchByName(phones, 4, searching_name, index1);
    if (i != -1) {
        printf("Абонент с именем '%s' найден. Его индекс в массиве - [%d]\n", searching_name, i);
    } else {
        printf("Абонент с именем '%s' не найден.\n", searching_name);
    }

    printf("\nДвоичный поиск по номеру телефона:\n");
    long searching_num = 223455;
    i = BinarySearchByNumber(phones, 4, searching_num, index2);
    if (i != -1) {
        printf("Абонент с номером '%ld' найден. Его индекс в массиве - [%d]\n", searching_num, i);
    } else {
        printf("Абонент с номером '%ld' не найден.\n", searching_num);
    }

    
    return 0;
}

