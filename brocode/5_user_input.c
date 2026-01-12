#include <stdio.h>
#include <string.h>

int main()
{
    int a;
    printf("%d\n", a); // print whatever was in the memory

    // best practice to assign zero values to the variables
    int i = 0;
    float f = 0.0f;
    char c = '\0';  // null terminator
    char s[30] = "";

    printf("int: ");
    scanf("%d", &i);  // the address of i

    printf("flaot: ");
    scanf("%f", &f);

    printf("char: ");
    scanf(" %c", &c);  // add space to skip \n from the previous input. clear the buffer

    // printf("string: ");
    // scanf("%s", &s); // won't store after a white space, use fgets

    printf("fgets: ");  // file get string
    getchar();  // clear the buffer
    fgets(s, sizeof(s), stdin);  // var, size, stdin
    s[strlen(s) - 1] = '\0';  // replace \n with \0

    printf("int: %d\n", i);
    printf("float: %f\n", f);
    printf("char: %c\n", c);
    printf("string: %s\n", s);
    printf("fgets: %s\n", s);

    return 0;
}
