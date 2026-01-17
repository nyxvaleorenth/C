#include <stdio.h>

int main() {
    int week_day = 0;
    printf("Enter the day of the week number: ");
    scanf("%d", &week_day);

    switch(week_day) {
        case 1:
            printf("Saturday");
            break;
        case 2:
            printf("Sunday");
            break;
        case 3:
            printf("Monday");
            break;
        case 4:
            printf("Tuesday");
            break;
        case 5:
            printf("Wednesday");
            break;
        case 6:
            printf("Thursday");
            break;
        case 7:
            printf("Friday");
            break;
        default:
            printf("HI!");
    }

    return 0;
}
