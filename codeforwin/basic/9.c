/* find angles of triangle if two angles are given */
#include <stdio.h>

int main() {
    float angle1 = 0.0f;
    float angle2 = 0.0f;
    float angle3 = 0.0f;

    printf("Enter angle 1: ");
    scanf("%f", &angle1);

    printf("Enter angle 2: ");
    scanf("%f", &angle2);

    angle3 = 180 - (angle1 + angle2);

    printf("angle 3 = %.2f\n", angle3);

    return 0;
}
