#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!(p = malloc(s))) {\
        fprintf(stderr, "Insufficent memory"); \
        exit(EXIT_FAILURE); \
    }

int* func1(void) {
    int* p;

    MALLOC(p, sizeof(int));

    *p = 10;

    return p;
}

void func2(int* p) {
    *p = 100;
}

void func3(int** dp) {
    **dp = 200;
}

char* func4(int size) {
    char* p;

    MALLOC(p, sizeof(int));

    return p;
}

int main(void) {
    int* pNum;
    char* pChar;

    pNum = func1(); // int ũ�⸸ŭ �����Ҵ� �޾� 10�� ������ ������ ������ ����
    printf("%d\n", *pNum);

    func2(pNum); // pNum�� ����Ű�� ���� 100���� ����
    printf("%d\n", *pNum);

    func3(&pNum); // pNum�� ����Ű�� ���� 200���� ����
    printf("%d\n", *pNum);

    pChar = func4(100);

    printf("\n�Է��� ���ڿ� : ");
    gets_s(pChar, 100);
    printf("pChar contents = %s\n", pChar);

    free(pNum);
    free(pChar);
    return 0;
}