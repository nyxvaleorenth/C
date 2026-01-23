#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_DIGITS 3
#define MAX_GUESSES 10
#define BUFFER_SIZE 100

void printInstructions(void);
void getSecretNum(char *secretNum);
void getClues(const char *guess, const char *secretNum, char *result);
int isValidGuess(const char *guess);
void clearInputBuffer(void);

int main(void) {
    srand((unsigned int)time(NULL));

    printInstructions();

    while (1) {
        char secretNum[NUM_DIGITS+1];

        getSecretNum(secretNum);

        printf("I have thought up a number.\n");
        printf(" You have %d guesses to get it.\n", MAX_GUESSES);

        int numGuesses = 1;

        while (numGuesses <= MAX_GUESSES) {
            char input[BUFFER_SIZE];
            char guess[NUM_DIGITS + 1];

            while(1) {
                printf("Guess #%d: \n> ", numGuesses);

                if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
                    printf("Error reading input.\n");
                    continue;
                }
                input[strcspn(input, "\n")] = '\0';

                if (strlen(input) != NUM_DIGITS) {
                    continue;
                }

                if (!isValidGuess(input)) {
                    continue;
                }

                strcpy(guess, input);
                break;
            }

            char result[50];
            getClues(guess, secretNum, result);
        }
    }
}
