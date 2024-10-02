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

    pNum = func1(); // int 크기만큼 동적할당 받아 10을 저장후 정수형 포인터 리턴
    printf("%d\n", *pNum);

    func2(pNum); // pNum이 가리키는 것을 100으로 수정
    printf("%d\n", *pNum);

    func3(&pNum); // pNum이 가리키는 것을 200으로 수정
    printf("%d\n", *pNum);

    pChar = func4(100);

    printf("\n입력할 문자열 : ");
    gets_s(pChar, 100);
    printf("pChar contents = %s\n", pChar);

    free(pNum);
    free(pChar);
    return 0;
}