#include <stdio.h>

int main()
{
    int i = 1;
    int ni = -10;

    // width - rjustify
    printf("%3d\n", i);
    // width - ljustify
    printf("%-3d\n", i);
    // fill
    printf("%03d\n", i);
    // negative
    printf("%+d\n", i);
    printf("%+d\n", ni);

    // precision
    float f = 15.139415;

    printf("%.2f\n", f);  // round 15.139 ~ 15.14

    // combine everything
    printf("%+09.3f\n", f);

    return 0;
}
