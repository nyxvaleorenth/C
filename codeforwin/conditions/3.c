/* check even or odd number
inputs: number
output: even or odd
prodedure:
 define number
 input number

 if number % 2 == 0: print even else odd
*/
#include <stdio.h>

int main() {
    int num;

    printf("Enter the number: ");
    scanf("%d", &num);

    if (num % 2 == 0) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}
