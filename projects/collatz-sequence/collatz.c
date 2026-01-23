#include <stdio.h>    // printf, fgets
#include <stdlib.h>   // atoll
#include <string.h>   // strlen strcspn
#include <ctype.h>    // isdigit
#include <time.h>     // nanosleep
#include <unistd.h>   // use nanosleep

#define SLEEP_MS(ms) usleep((ms) * 1000)


int is_valid_number(const char *str) {
    if (str == NULL || str[0] == '\0'){
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++){
        if (!isdigit((unsigned char)str[i])){
            return 0;
        }
    }
    return 1;
}

int main(void){
    char input[100];
    long long n;

    printf("Enter a number greater than zero (or QUIT): ");
    if (fgets(input, sizeof(input), stdin) == NULL){
        printf("Error while reading input.");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0) {
        printf("Goodbye!\n");
        return 0;
    }

    if (!is_valid_number(input)) {
        printf("Please enter an integer greater than 0.\n");
        return 1;
    }

    n = atoll(input);

    if (n <= 0){
        printf("Please enter an integer greater than 0.\n");
        return 1;
    }

    printf("%lld", n);
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
    return 0;
}
