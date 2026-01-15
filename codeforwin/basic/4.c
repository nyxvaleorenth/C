/* find perimeter of a rectangle giving its length and width */
#include <stdio.h>

int main()
{
    int width = 0;
    int length = 0;
    int perimeter = 0;

    printf("Enter length: ");
    scanf("%d", &length);

    printf("Enter width: ");
    scanf("%d", &width);

    perimeter = 2 * (length + width);

    printf("Perimeter of rectangle = %d units\n", perimeter);

    return 0;
}
