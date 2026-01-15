/* convert temperature from degree celsius to fahrenheit */
#include <stdio.h>

int main() {
    float celsius = 0.0f;
    float fahrenheit = 0.0f;

    printf("Enter degree in Celsius: ");
    scanf("%f", &celsius);

    fahrenheit = (9.0 / 5.0) * celsius + 32;

    printf("%.2fC = %.2fF\n", celsius, fahrenheit);

    return 0;
}
