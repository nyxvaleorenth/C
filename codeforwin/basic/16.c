/* calculate total average and percentage of five subjects */
#include <stdio.h>

int main() {
    int s1, s2, s3, s4, s5;
    int total;
    float average, percentage;

    printf("Enter the marks (seperated with a space): ");
    scanf("%d %d %d %d %d", &s1, &s2, &s3, &s4, &s5);

    total = s1 + s2 + s3 + s4 + s5;

    average = total / 5.0;

    percentage = total / 500.0 * 100.0;

    printf("Total: %d\n", total);
    printf("Average: %.2f\n", average);
    printf("Percentage: %.2f\n", percentage);

    return 0;
}
