/* find maximum between three numbers
input: 3 numbers
output: maximum of the 3 numbers
procedure:
 define num1, num2, num3, max
 input num1, num2, num3

 if num1 > num2 and num3: max = num1
 else if num2 > num1 and num3: max = num2
 else max = num3

 print max
*/

#include <stdio.h>

int main() {
    int num1, num2, num3, max;

    printf("Enter 3 number:\n");
    scanf("%d%d%d", &num1, &num2, &num3);

    if (num1 > num2 && num1 > num3) {
        max = num1;
    } else if (num2 > num3) {
        max = num2;
    } else {
        max = num3;
    }

    printf("The maximum of %d, %d and %d is %d\n", num1, num2, num3, max);

    return 0;
}
