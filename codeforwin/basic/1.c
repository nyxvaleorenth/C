/* C program to perform input output of all basic data types */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    int d = 0;
    float f = 0.0f;
    double lf = 0.0;
    char c = '\0';
    char string[50] = "hello";
    bool b = false;

    printf("int: ");
    scanf("%d", &d);

    printf("float: ");
    scanf("%f", &f);

    printf("double: ");
    scanf("%lf", &lf);

    printf("char: ");
    scanf(" %c", &c);

    printf("string: ");
    getchar();
    fgets(string, sizeof(string), stdin);
    string[strlen(string) - 1] = '\0';

    printf("bool: ");
    scanf("%d", &b);

    printf("int: %d\n", d);
    printf("float: %f\n", f);
    printf("double: %lf\n", lf);
    printf("char: %c\n", c);
    printf("string: %s\n", string);
    printf("bool: %d\n", b);

    return 0;
}
