/* find power of a number using pow function */
#include <stdio.h>
#include <math.h>

int main() {
    float base = 0.0f;
    float exponent = 0.0f;
    float result = 0.0f;

    printf("Enter the base: ");
    scanf("%f", &base);

    printf("Enter the exponent: ");
    scanf("%f", &exponent);

    result = pow(base, exponent);

    printf("%.2f^%.2f = %.2f\n", base, exponent, result);

    return 0;
}
