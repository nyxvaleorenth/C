#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)


int is_valid_number(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }

    return 1;
}


int main(void) {
    char input[100];
    long long n;

    printf("The Collatz sequence is a sequence of numbers produced from a starting\n");
    printf("number n, following three rules\n\n");
    printf("1) If n is even, the next number n is n / 2");
    printf("2) If n is odd, the next number n is n * 3 + 1");
    printf("3) If n is 1, stop. Otherwise, repeat\n\n");
    printf("every starting number eventually terminates at 1\n\n");

    printf("Enter a starting number (greater than 0) or QUIT:\n");

    if (fgets(input, sizeof(input), stdin) == NULL){
        printf("Error reading input.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0) {
        printf("Goodbye!\n");
        return 0;
    }

    if (!is_valid_number(input)) {
        printf("You must enter an integer greater than 0.\n");
        return 0;
    }

    n = atoll(input);

    if (n <= 0){
        printf("You must enter an integer greater than 0.\n");
        return 1;
    }

    printf("%lld, ", n);
    fflush(stdout);

    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }

        printf(", %lld", n);
        fflush(stdout);

        SLEEP_MS(100);
    }
    printf("\n");
}
