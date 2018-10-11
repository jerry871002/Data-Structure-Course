#include <stdio.h>

void fib(int n)
{
	long num1 = 0;
	long num2 = 1;
	long ans = n;

    if(n == 1)
        printf("%ld", num2);
    else {
        printf("%ld, ", num2);
        for (long i = 2; i <= n; i++) {
    		ans = num1 + num2;
    		num1 = num2;
    		num2 = ans;
            printf("%ld", ans);
            if(i != n)
                printf(", ");
    	}
    }
    printf("\n");
}

int main() {
    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);
    fib(num);
    return 0;
}
