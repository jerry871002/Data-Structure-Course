#include <stdio.h>

int ackerman(int m, int n) {
    if(m == 0) {
        printf("return %d + 1\n", n);
        return n + 1;
    }
    else if(n == 0 && m > 0) {
        printf("return ackerman(%d, 1)\n", m-1);
        return ackerman(m-1, 1);
    }
    else {
        printf("return ackerman(%d, ackerman(%d, %d))\n", m-1, m, n-1);
        return ackerman(m-1, ackerman(m, n-1));
    }
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", ackerman(a, b));
    return 0;
}
