/*
find area of an equilateral triangle

input: side length of the traingle
output: area of the triangle
procedure:

import math
define side, area
input side
area = sqrt(3)/4 * 4^2
print area
*/

#include <stdio.h>
#include <math.h>

int main() {
    float side, area;

    printf("Enter side of an equilateral triangle: ");
    scanf("%f", &side);

    area = sqrt(3)/4.0 * pow(side, 2);

    printf("Area of equilateral triangle = %.2f sq. units\n", area);

    return 0;
}
