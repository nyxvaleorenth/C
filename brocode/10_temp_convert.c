/* tempurature converter */
#include <stdio.h>

int main() {
    char choice = '\0';
    float celsius = 0.0f;
    float fahrenheit = 0.0f;
    float result = 0.0f;

    printf("Enter your choice: \n");
    printf("  (C) Celsius to Fahrentheit\n");
    printf("  (F) Fahrentheit to Celsius\n");
    printf("  >>> ");
    scanf("%c", &choice);

    if (choice == 'C') {
        printf("Enter the degree in Celsius: ");
        scanf("%f", &celsius);
        result = celsius * (9.0 / 5.0) + 32;
        printf("%.2fC = %.2fF\n", celsius, result);
    } else if (choice == 'F') {
        printf("Enter the degree in Fahrentheit: ");
        scanf("%f", &fahrenheit);
        result = (fahrenheit - 32) * (5.0 / 9.0);
        printf("%.2fF = %.2fC\n", fahrenheit, result);
    } else {
        printf("Please enter a valid choice");
    }



    return 0;
}
