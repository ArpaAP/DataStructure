#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKETS 11

int compareCount = 0;

typedef struct {
	char key[100];
	int value;
} element;

typedef struct node* nodePointer;
typedef struct node {
	element data;
	nodePointer link;
} node;

unsigned int stringToInt(char* s) {
	int number = 0;
	while (*s) number += *s++;
	return number;
}

unsigned int hash(unsigned int key)
{
	return key % BUCKETS;
}

void insert(nodePointer hashTable, char* key)
{
	int value = stringToInt(key);
	int index = hash(value);

	nodePointer p = (nodePointer)malloc(sizeof(node));
	p->data.value = value;
	p->link = NULL;
	strcpy(p->data.key, key);

	nodePointer q = hashTable[index].link;

	if (!q)
	{
		hashTable[index].link = p;
		return;
	}

	while (q->link) q = q->link;
	q->link = p;
}

element search(nodePointer hashTable, char* key)
{
	compareCount = 0;

	int value = stringToInt(key);
	int index = hash(value);
	nodePointer p = hashTable[index].link;
	while (p)
	{
		compareCount++;
		if (p->data.value == value)
		{
			return p->data;
		}
		p = p->link;
	}
	element e;
	e.value = -1;
	return e;
}

void display(nodePointer hashTable)
{
	printf("         (item, key)\n");
	for (int i = 0; i < BUCKETS; i++)
	{
		nodePointer p = hashTable[i].link;
		printf("ht[%2d] : ", i);
		while (p)
		{
			printf("(%s %d) ", p->data.key, p->data.value);
			p = p->link;
		}
		printf("\n");
	}
}

int main()
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("Error opening file\n");
		return 1;
	}

	nodePointer hashTable = (nodePointer)malloc(sizeof(node) * BUCKETS);

	for (int i = 0; i < BUCKETS; i++)
	{
		hashTable[i].data.value = -1;
		hashTable[i].link = NULL;
	}

	printf(" input strings : ");

	char key[100];

	while (fscanf(f, "%s", key) != EOF)
	{
		insert(hashTable, key);
		printf("%s ", key);
	}
	printf("\n\n");

	display(hashTable);

	while (1)
	{
		printf("\ninput \"quit\" to quit\n");
		printf("string to search >> ");
		scanf("%s", key);
		if (!strcmp(key, "quit")) break;

		element e = search(hashTable, key);

		if (e.value == -1)
		{
			printf("It doesn't exist!\n");
		}
		else
		{
			printf("item : %s, key : %d, the number of comparisions : %d\n", e.key, e.value, compareCount);
		}

	}

	fclose(f);

	return 0;
}