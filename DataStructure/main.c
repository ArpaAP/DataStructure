// 문제1
//#include <stdio.h>
//#include <stdlib.h>
//
//int* func1(void) {
//    int *p = (int *) malloc(sizeof(int));
//    
//    return p;
//}
//
//void func2(int *p) {
//    *p = 100;
//}
//
//void func3(int **dp) {
//    **dp = 200;
//}
//
//char* func4(int size) {
//    char *p = (char *) malloc(size);
//    
//    return p;
//}
//
//int main(void) {
//    int *pNum;
//    char *pChar;
//
//    pNum = func1(); // int 크기만큼 동적할당 받아 10을 저장후 정수형 포인터 리턴
//    printf("%d\n", *pNum);
//    
//    func2(pNum); // pNum이 가리키는 것을 100으로 수정
//    printf("%d\n", *pNum);
//    
//    func3(&pNum); // pNum이 가리키는 것을 200으로 수정
//    printf("%d\n", *pNum);
//    
//    pChar = func4(100);
//    
//    printf("\n입력할 문자열 : ");
//    scanf_s("%s", pChar, sizeof(pChar));
//    printf("pChar contents = %s\n", pChar);
//    
//    free(pNum);
//    free(pChar);
//    return 0;
//}


// 문제 2

#include <stdio.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 1001

int main(void) {
    FILE* f;
    
    if ((f = fopen("out.txt", "w")) == NULL) {
        printf("error on opening file\n");
        return 1;
    }
    
    int step = 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;
    
    fprintf(f, "       n      time\n");
    
    for (int n = 0; n <= 1000; n += step) {
        for (int i = 0; i < n; i++) {
            a[i] = n - i;
        }
        
        start = clock();
        sort(a, n);
        duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
        
        fprintf(f, "%6d\t%f\n", n, duration);
        if (n == 100) step = 100;
    }
    
    fclose(f);
    
    return 0;
}
