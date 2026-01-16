/* find square root of a number */
#include <stdio.h>
#include <math.h>

int main() {
    float num = 0.0f;
    float result = 0.0f;

    printf("Enter a number: ");
    scanf("%f", &num);

    result = sqrt(num);

    printf("sqrt(%.2f) = %.2f\n", num, result);

    return 0;
}
