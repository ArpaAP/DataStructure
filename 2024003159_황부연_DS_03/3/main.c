#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

typedef struct {
	char name[50];
	int age;
	int salary;
} humanBeing;

int humansEqual(humanBeing* person1, humanBeing* person2)
{
	if (strcmp(person1->name, person2->name))
		return FALSE;

	if (person1->age != person2->age)
		return FALSE;

	if (person1->salary != person2->salary)
		return FALSE;

	return TRUE;
}

int main(void)
{
	humanBeing p1, p2;

	printf("Input person1's name, age, salary : \n");
	gets_s(p1.name, 50);
	scanf_s("%d %d", &p1.age, &p1.salary);
	getchar();

	printf("Input person2's name, age, salary : \n");
	gets_s(p2.name, 50);
	scanf_s("%d %d", &p2.age, &p2.salary);

	int equal = humansEqual(&p1, &p2);

	if (equal)
		printf("The two human beings are the same\n");
	else
		printf("The two human beings are not the same\n");

	return 0;
}