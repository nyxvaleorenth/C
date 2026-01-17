/*
find area of a triangle

input: base, height
output: area
procedure:

define base, height, area
input base, height
area = base * height / 2
print area
*/

#include <stdio.h>

int main() {
    float base, height, area;

    printf("Enter the base: ");
    scanf("%f", &base);

    printf("Enter the height: ");
    scanf("%f", &height);

    area = (base * height) / 2.0;

    printf("Area of the triangle = %.2f sq. units\n", area);

    return 0;
}
