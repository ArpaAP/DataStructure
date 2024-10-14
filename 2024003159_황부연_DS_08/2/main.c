#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
	char belonging[100];
	char gender[100];
	struct listNode* next;
} listNode;

listNode* first = NULL;
listNode* maleFirst = NULL;
listNode* femaleFirst = NULL;

void printList(listNode* first)
{
	listNode* current = first;

	int i = 1;

	while (current != NULL)
	{
		printf("(%p, %s, %s, %s, %p)", current, current->name, current->belonging, current->gender, current->next);
		current = current->next;

		if (i % 2 == 0) printf("\n");
		i++;
	}

	if (i % 2 != 1) printf("\n");
}

listNode* insert(listNode* first, listNode* target, listNode* newNode)
{
	if (first == NULL)
	{
		newNode->next = NULL;
		first = newNode;
	}
	else {
		newNode->next = target->next;
		target->next = newNode;
	}

	return first;
}

listNode* concatenate(listNode* first, listNode* second)
{
	listNode* temp;

	if (!first) return second;
	if (!second) return first;

	for (temp = first; temp->next; temp = temp->next);

	temp->next = second;

	return first;
}

listNode* invert(listNode* first)
{
	listNode *middle, *trail;
	middle = NULL;

	while (first)
	{
		trail = middle;
		middle = first;
		first = first->next;
		middle->next = trail;
	}

	return middle;
}

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("Cannot open file.\n");
		return 1;
	}

	listNode* current = first;
	while (!feof(f))
	{
		listNode* node = (listNode*)malloc(sizeof(listNode));
		fscanf(f, "%s %s %s", node->name, node->belonging, node->gender);

		first = insert(first, current, node);
		current = node;
	}

	fclose(f);

	printf("전체 리스트\n");

	printList(first);

	// 남녀 리스트 분리

	current = first;
	listNode* maleCurrent = maleFirst;
	listNode* femaleCurrent = femaleFirst;

	while (current != NULL)
	{
		listNode* node = (listNode*)malloc(sizeof(listNode));

		if (strcmp(current->gender, "남자") == 0)
		{
			memcpy(node, current, sizeof(listNode));

			maleFirst = insert(maleFirst, maleCurrent, node);

			maleCurrent = node;
		}
		else
		{
			memcpy(node, current, sizeof(listNode));

			femaleFirst = insert(femaleFirst, femaleCurrent, node);

			femaleCurrent = node;
		}

		current = current->next;
	}

	

	printf("\n남자 리스트\n");
	printList(maleFirst);

	printf("\n여자 리스트\n");
	printList(femaleFirst);

	// 여자 리스트 뒤에 남자 리스트 연결
	
	listNode* concatedFirst = concatenate(femaleFirst, maleFirst);

	printf("\n합친 리스트\n");
	printList(concatedFirst);

	// 역순으로 출력

	listNode* invertedFirst = invert(concatedFirst);

	printf("\ninversed list\n");
	printList(invertedFirst);

	return 0;
}