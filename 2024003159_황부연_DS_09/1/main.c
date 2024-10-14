#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACKS 3
#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int class_num;
	int score;
} element;

typedef struct stackNode* stackPointer;

typedef struct stackNode {
	element data;
	stackPointer next;
} stackNode;



stackPointer top[MAX_STACKS];

void push(int i, element item)
{
	stackPointer temp = (stackPointer)malloc(sizeof(stackNode));

	temp->data = item;
	temp->next = top[i];
	top[i] = temp;
}

void print()
{
	stackPointer current;

	printf("과목번호, 학반, 성적\n");
	for (int i = 0; i < MAX_STACKS; i++)
	{
		printf("********************\n");

		current = top[i];
		while (current != NULL)
		{
			element item = current->data;
			printf("%8d %5d %4d\n", i, item.class_num, item.score);
			current = current->next;
		}
	}
}

int main() {
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL) {
		printf("Error opening file\n");
		return 1;
	}
	
	for (int i = 0; i < MAX_STACKS; i++) {
		top[i] = NULL;
	}

	int subject_num, class_num, score;
	while (!feof(f))
	{
		fscanf(f, "%d %d %d", &subject_num, &class_num, &score);

		element item;
		item.class_num = class_num;
		item.score = score;

		push(subject_num, item);
	}

	fclose(f);

	print();
	
	return 0;
}