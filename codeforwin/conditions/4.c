/*  check leap year */
#include <stdio.h>

int main() {
    int year;
    printf("Enter the year: ");
    scanf("%d", &year);

    if ((year % 4 == 0) && !(year % 100 == 0)){
        printf("Leap");
    } else if (year % 400 == 0) {
        printf("Leap");
    } else {
        printf("Common");
    }

    return 0;
}
