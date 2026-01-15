#include <stdio.h>

int main()
{
    float cm = 0.0f;
    float m = 0.0f;
    float km = 0.0f;

    printf("Enter length in cm: ");
    scanf("%f", &cm);

    m = cm / 100;
    km = m / 1000;

    printf("m = %f\n", m);
    printf("km = %f\n", km);

    return 0;
}
