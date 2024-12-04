#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKETS 11
#define MAX_KEY_LENGTH 100

int compareCount = 0;

typedef struct {
    char key[MAX_KEY_LENGTH];
    int value;
} element;

unsigned int stringToInt(char* key) {
    int number = 0;
    while (*key) number += *key++;
    return number;
}

unsigned int hash(unsigned int k) {
    return k % BUCKETS;
}

void insert(element* table, char* key) {
    int value = stringToInt(key);
    int index = hash(value);

    while (table[index].value != -1) {
        index = (index + 1) % BUCKETS;
    }

    strcpy(table[index].key, key);
    table[index].value = value;
}

int search(element* table, char* key) {
	compareCount = 1;

	int value = stringToInt(key);
	int index = hash(value);

	while (table[index].value != value) {
		index = (index + 1) % BUCKETS;
		if (table[index].value == -1) {
			compareCount++;
			return -1;
		}
		compareCount++;
	}
	return index;
}

void display(element* table) {
    printf("             item      key\n");

    for (int i = 0; i < BUCKETS; i++) {
        printf("ht[%2d] : ", i);
        if (table[i].value != -1) {
            printf("%8s %8d", table[i].key, table[i].value);
        }
        printf("\n");
    }
}

int main() {
    FILE* f;

    if ((f = fopen("input.txt", "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    element table[BUCKETS];
    for (int i = 0; i < BUCKETS; i++) {
        table[i].value = -1;
        table[i].key[0] = '\0';
    }

    char key[MAX_KEY_LENGTH];
    while (fscanf(f, "%s", key) != EOF) {
        insert(table, key);
    }

    display(table);

	char searchKey[MAX_KEY_LENGTH];
    printf("\nstring to search >> ");
	scanf("%s", searchKey);

	int index = search(table, searchKey);
	if (index == -1) {
		printf("It doesn't exist!\n");
	}
    else {
        printf("item : %s, key: %d, the number of comparisions : %d\n", table[index].key, table[index].value, compareCount);
    }

    fclose(f);

    return 0;
}
