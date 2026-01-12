#include <stdio.h>

int main()
{
    int a = 5;
    int b = 9;
    int c = 0;

    // addition
    c = a + b;
    printf("%d\n", c);

    // subtraction
    c = a - b;
    printf("%d\n", c);

    // mutliplication
    c = a * b;
    printf("%d\n", c);

    // division
    // we use floats cause ints can't store numbers after the decimal point
    float x = 5.0;
    float y = 9.0;
    float z = 0.0;

    z = x / y;
    printf("%f\n", z);

    // integer remainder
    c = a % b;
    // z = x % y;  doesn't work with floats
    printf("%d\n", c);

    // increment and decrement
    int d = 0;
    d++;
    printf("%d\n", d);

    d--;
    printf("%d\n", d);

    // augmented assignment
    int r = 10;

    r += 1;
    printf("%d\n", r);

    r -= 1;
    printf("%d\n", r);

    r *= 5;
    printf("%d\n", r);

    r /= 5;
    printf("%d\n", r);

    r %= 2;
    printf("%d\n", r);

    return 0;
}
