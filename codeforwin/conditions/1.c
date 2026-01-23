/* find maximum between two numbers
input: two numbers
output: the maximum of the two numbers
procedure:
 define num1, num2, max
 input num1, num2
 if num1 > num2: max = num1 else max = num2
 print max
*/
#include <stdio.h>

int main() {
    int num1, num2, max;

    printf("Enter two numbers (separated by a space): \n");
    scanf("%d%d", &num1, &num2);

    if (num1 > num2) {
        max = num1;
    } else {
        max = num2;
    }

    printf("The maximum between %d and %d is %d\n", num1, num2, max);

    return 0;
}
