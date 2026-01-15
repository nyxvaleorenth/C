/* find are of a rectangle */
#include <stdio.h>

int main()
{
    float length = 0.0f;
    float width = 0.0f;
    float area = 0.0f;

    printf("Enter length: ");
    scanf("%f", &length);

    printf("Enter width: ");
    scanf("%f", &width);

    area = length * width;

    printf("Area of ractangle = %.2f sq. units\n", area);

    return 0;
}
