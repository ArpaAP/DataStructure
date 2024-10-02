
#include <stdio.h>

int sumAry2D_f1(int ary[][3], int ROW, int COL) {
    int sum = 0;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            sum += ary[i][j];
        }
    }

    return sum;
}

int sumAry2D_f2(int (*ary)[3], int ROW) {
    int sum = 0;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < 3; j++) {
            sum += ary[i][j];
        }
    }

    return sum;
}

int sumAry2D_f3(int ary[3][3]) {
    int sum = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += ary[i][j];
        }
    }

    return sum;
}

int main(void) {
    int ROW = 3, COL = 3;

    int ary2D[][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, ROW, COL));
    printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, ROW));
    printf("sumAry2D_f3() %d\n\n", sumAry2D_f3(ary2D));

    return 0;
}