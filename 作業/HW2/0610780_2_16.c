#include <stdio.h>
#include <math.h>

double squareRoot(double num, double ans, double tol) {
    if(fabs(ans*ans-num) <= tol)
        return ans;
    else
        return squareRoot(num, (ans*ans+num)/(2*ans), tol);
}

int main() {
    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);
    printf("The square root of %d is %lf\n", num, squareRoot(num, 2, 0.01));
    return 0;
}
