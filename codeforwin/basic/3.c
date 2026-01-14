#include <stdio.h>

int main()
{
    int num1, num2;
    int sum, sub, prod, mod;
    float div;

    printf("Enter num1, hit Enter, enter num2\n");
    scanf("%d%d", &num1, &num2);

    sum = num1 + num2;
    sub = num1 - num2;
    prod = num1 * num2;
    div = num1 / num2;
    mod = num1 % num2;

    printf("%d + %d = %d\n", num1, num2, sum);
    printf("%d - %d = %d\n", num1, num2, sub);
    printf("%d * %d = %d\n", num1, num2, prod);
    printf("%d / %d = %.2f\n", num1, num2, div);
    printf("%d %% %d = %d\n", num1, num2, mod);

    return 0;
}
