/* find diameter circumference and are of circle */
#include <stdio.h>
#include <math.h>

int main()
{
    const double PI = 3.14159265359;  // or M_PI from math.h
    float radius = 0.0f;
    float diameter = 0.0f;
    float circumference = 0.0f;
    float area = 0.0f;

    printf("Enter radius: ");
    scanf("%f", &radius);

    diameter = 2 * radius;
    circumference = 2 * PI * radius;
    area = PI * pow(radius, 2);

    printf("Diameter = %.2f units\n", diameter);
    printf("Circumference = %.2f units\n", circumference);
    printf("Area = %.2f sq. units\n", area);

    return 0;
}
