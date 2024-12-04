#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BUCKETS 8
#define MAX_KEYS 100

int rnums[BUCKETS];
int hashTable[BUCKETS] = { 0, };
int compareCount = 0;

unsigned int hash(unsigned int key)
{
	return key % BUCKETS;
}

void insert(int key)
{
	int index = hash(key);
	if (hashTable[index] == 0)
	{
		hashTable[index] = key;
	}
	else
	{
		int i = 1;
		while (1)
		{
			int newIndex = (index + rnums[i]) % BUCKETS;
			if (hashTable[newIndex] == 0)
			{
				hashTable[newIndex] = key;
				break;
			}
			i++;
		}
	}
}

void printHashTable()
{
	printf("\n         key\n");
	for (int i = 0; i < BUCKETS; i++)
	{
		printf("ht[%d] : ", i);
		if (hashTable[i] != 0)
		{
			printf("%3d", hashTable[i]);
		}
		printf("\n");
	}
}

int search(int key)
{
	compareCount = 0;
	int index = hash(key);

	compareCount++;
	if (hashTable[index] == key)
	{
		return index;
	}
	else
	{
		for (int i = 1; i < BUCKETS; i++)
		{
			int newIndex = (index + rnums[i]) % BUCKETS;

			compareCount++;
			if (hashTable[newIndex] == key)
			{
				
				return newIndex;
			}
		}
		return -1;
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

	int keys[MAX_KEYS];

	printf("key sequence from file : ");

	int c = 0;
	while (fscanf(f, "%d", &keys[c]) == 1)
	{
		printf("%5d ", keys[c]);
		c++;
	}
	printf("\n");

	unsigned int seed;
	printf("input seed >> ");
	scanf("%u", &seed);

	srand(seed);

	for (int i = 1; i < BUCKETS; i++)
	{
		rnums[i] = (rand() % (BUCKETS - 1)) + 1;

		for (int j = 0; j < i; j++)
		{
			if (rnums[i] == rnums[j])
			{
				i--;
				break;
			}
		}
	}

	printf("\n");
	for (int i = 1; i < BUCKETS; i++)
	{
		printf("randNum[%d] : %2d\n", i, rnums[i]);
	}

	for (int i = 0; i < c; i++)
	{
		insert(keys[i]);
	}

	printHashTable();

	int key;

	while (1)
	{
		printf("\ninput 0 to quit\n");
		printf("key to search >> ");
		scanf("%d", &key);

		if (!key) break;
		int index = search(key);
		
		if (index == -1)
		{
			printf("It doesn't exist!\n", key);
		}
		else
		{
			printf("key : %d, the number of comparisions: %d\n", hashTable[index], compareCount);
		}
	}

	fclose(f);

	return 0;
}