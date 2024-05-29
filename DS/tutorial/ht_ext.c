#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person {
    char name[MAX_NAME];
    int age;
    // Other data
    struct person *next;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i <length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }

    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_hash_table() {
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t", i);
            person *temp = hash_table[i];
            while (temp != NULL) {
                printf("%s - ", temp->name);
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup (char *name) {
    int index = hash(name);
    person *temp = hash_table[index];
    while (temp != NULL && strcmp(hash_table[index]->name, name) != 0) {
        temp = temp->next;
    }
    return temp;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    person *temp = hash_table[index];
    person *prev = NULL;
    while (temp != NULL && strcmp(hash_table[index]->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return NULL;
    if (prev == NULL) {
        hash_table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    return temp;
}

int main(void) {
    init_hash_table();
    print_hash_table();

    person jacob = {.name = "Jacob", .age = 256};
    person kate = {.name = "Kate", .age = 27};
    person mpho = {.name = "Mpho", .age = 14};
    person sarah = {.name = "Sarah", .age = 54};
    person edna = {.name = "Edna", .age = 15};
    person maren = {.name = "Maren", .age = 25};
    person eliza = {.name = "Eliza", .age = 34};
    person robert = {.name = "Robert", .age = 1};
    person jane = {.name = "Jane", .age = 75};

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);

    print_hash_table();

    person *temp = hash_table_lookup("Mpho");

    if (temp == NULL) {
        printf("Not found\n");
    } else {
        printf("Found %s.\n", temp->name);
    }

    temp = hash_table_lookup("George");

    if (temp == NULL) {
        printf("Not found\n");
    } else {
        printf("Found %s.\n", temp->name);
    }

    hash_table_delete("Mpho");

    temp = hash_table_lookup("George");

    if (temp == NULL) {
        printf("Not found\n");
    } else {
        printf("Found %s.\n", temp->name);
    }

    print_hash_table();

    return 0;
}