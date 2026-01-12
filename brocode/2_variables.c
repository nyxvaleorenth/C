#include <stdio.h>
#include <stdbool.h>  // for bool

int main()
{
    int i = 15;  // int truncate float. int i = 15.5; i will equal 15; 4 bytes
    float f = 1.99;  // can only store 6~7 digits after . accurately; 4 bytes
    double d = 3.14159265358979;  // 15~16 digits; 8 bytes
    char c = 'A';  // 1 byte
    char s[] = "string: char array";  // size varies
    bool b = true;  // true:1, false:0; 1 byte

    printf("int: %d\n", i);
    printf("float: %f\n", f);
    printf("double: %lf\n", d);
    printf("char: %c\n", c);
    printf("char array: %s\n", s);
    printf("bool: %d\n", b);

    return 0;
}
