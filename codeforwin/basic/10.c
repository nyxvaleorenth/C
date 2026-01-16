#include <stdio.h>

int main() {
    int days = 0;
    int weeks = 0;
    int years = 0;
    int original_days = 0;

    printf("Enter the days: ");
    scanf("%d", &days);
    original_days = days;

    years = days / 365;
    days -= years * 365;

    weeks = days / 7;
    days -= weeks * 7;

    printf("%d days = %d years, %d weeks, %d days\n", original_days, years, weeks, days);

    return 0;
}
