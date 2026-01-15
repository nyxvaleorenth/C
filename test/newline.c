#include <stdio.h>

int main()
{
    char s[50] = "";
    fgets(s, sizeof(s), stdin);

    printf("%s", s);

    return 0;
}
