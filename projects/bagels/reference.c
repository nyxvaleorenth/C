/*
 * Bagels - A deductive logic game
 * Converted from Python to idiomatic C
 */

#include <stdio.h>   // For printf, fgets, scanf - standard input/output functions
#include <stdlib.h>  // For rand, srand, atoi - standard library utilities
#include <string.h>  // For string manipulation functions like strlen, strcpy
#include <time.h>    // For time() - used to seed the random number generator
#include <ctype.h>   // For isdigit() - character type checking

/*
 * Constants: Using #define for compile-time constants (like Python's global variables)
 * These are replaced by the preprocessor before compilation
 */
#define NUM_DIGITS 3
#define MAX_GUESSES 10
#define BUFFER_SIZE 100  // Safe size for input buffer to prevent overflow

/*
 * Function Prototypes (Forward Declarations)
 * In C, we declare functions before using them so the compiler knows their signatures
 */
void printInstructions(void);
void getSecretNum(char *secretNum);
void getClues(const char *guess, const char *secretNum, char *result);
int isValidGuess(const char *guess);
void clearInputBuffer(void);

/*
 * Main Function - Entry point of the program
 * Returns int: 0 for success (Unix convention)
 */
int main(void) {
    /*
     * Seed the random number generator with current time
     * time(NULL) returns seconds since Unix epoch (Jan 1, 1970)
     * This ensures different random numbers each run
     */
    srand((unsigned int)time(NULL));

    // Print game instructions once at the start
    printInstructions();

    /*
     * Main game loop - continues until player chooses to quit
     * In C, we use while(1) for infinite loops (Python uses while True)
     */
    while (1) {
        /*
         * Declare secretNum as char array on the stack
         * Size is NUM_DIGITS + 1 to hold the null terminator '\0'
         * In C, strings are null-terminated character arrays
         */
        char secretNum[NUM_DIGITS + 1];

        // Generate the secret number
        getSecretNum(secretNum);

        printf("I have thought up a number.\n");
        printf(" You have %d guesses to get it.\n", MAX_GUESSES);

        /*
         * numGuesses: int counter for tracking attempts
         * Starting at 1 (not 0) for user-friendly display
         */
        int numGuesses = 1;

        // Inner loop - one complete round of guessing
        while (numGuesses <= MAX_GUESSES) {
            /*
             * Input buffer allocated on stack
             * BUFFER_SIZE (100) is much larger than needed for safety
             * Prevents buffer overflow attacks
             */
            char input[BUFFER_SIZE];
            char guess[NUM_DIGITS + 1];  // To store validated guess

            /*
             * Input validation loop
             * Keeps asking until user provides valid NUM_DIGITS input
             */
            while (1) {
                printf("Guess #%d: \n> ", numGuesses);

                /*
                 * fgets: Safer than gets() - prevents buffer overflow
                 * Reads up to BUFFER_SIZE-1 chars from stdin
                 * Parameters: (destination, max_size, input_stream)
                 * Returns NULL on error/EOF
                 */
                if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
                    printf("Error reading input.\n");
                    continue;
                }

                /*
                 * Remove newline character that fgets captures
                 * strcspn finds the position of '\n' in the string
                 * We replace it with '\0' (null terminator)
                 */
                input[strcspn(input, "\n")] = '\0';

                /*
                 * strlen: Returns length of string (not counting '\0')
                 * Check if input is exactly NUM_DIGITS characters
                 */
                if (strlen(input) != NUM_DIGITS) {
                    continue;  // Skip to next iteration if wrong length
                }

                // Validate that all characters are digits
                if (!isValidGuess(input)) {
                    continue;
                }

                /*
                 * strcpy: String copy function
                 * Copies input to guess (including null terminator)
                 * Safe here because we've validated the length
                 */
                strcpy(guess, input);
                break;  // Exit validation loop - we have valid input
            }

            /*
             * Generate and display clues
             * result array allocated on stack to hold clue string
             * Size 50 is enough for worst case: "Fermi Fermi Fermi" + '\0'
             */
            char result[50];
            getClues(guess, secretNum, result);
            printf("%s\n", result);

            // Increment guess counter
            numGuesses++;

            /*
             * strcmp: String comparison function
             * Returns 0 if strings are identical
             * In C, we can't use == to compare strings directly
             */
            if (strcmp(guess, secretNum) == 0) {
                break;  // Player won - exit guessing loop
            }

            // Check if player ran out of guesses
            if (numGuesses > MAX_GUESSES) {
                printf("You ran out of guesses.\n");
                printf("The answer was %s.\n", secretNum);
            }
        }

        // Ask if player wants to play again
        printf("Do you want to play again? (yes or no)\n> ");

        char playAgain[BUFFER_SIZE];
        if (fgets(playAgain, BUFFER_SIZE, stdin) != NULL) {
            /*
             * tolower: Converts character to lowercase
             * We check if first character is 'y' (case-insensitive)
             * Similar to Python's .lower().startswith('y')
             */
            if (tolower(playAgain[0]) != 'y') {
                break;  // Exit main game loop
            }
        }
    }

    printf("Thanks for playing!\n");

    /*
     * Return 0 to indicate successful program execution
     * This is a convention in Unix/Linux systems
     */
    return 0;
}

/*
 * Function: printInstructions
 * Displays the game rules and clue explanations
 * void parameter list means no parameters
 * void return type means no return value
 */
void printInstructions(void) {
    /*
     * Using multiple printf statements for clarity
     * Could use a single multi-line string, but this is more maintainable
     */
    printf("Bagels, a deductive logic game.\n");
    printf("I am thinking of a %d-digit number. Try to guess what it is.\n", NUM_DIGITS);
    printf("Here are some clues:\n");
    printf("When I say:    That means:\n");
    printf("  Pico         One digit is correct but in the wrong position.\n");
    printf("  Fermi        One digit is correct and in the right position.\n");
    printf("  Bagels       No digit is correct.\n\n");
    printf("For example, if the secret number was 248 and your guess was 843, the\n");
    printf("clues would be Fermi Pico.\n\n");
}

/*
 * Function: getSecretNum
 * Generates a random NUM_DIGITS number with unique digits
 *
 * Parameters:
 *   char *secretNum - Pointer to char array where result will be stored
 *                     We modify the caller's array (pass by reference)
 *
 * Memory: Works with caller's stack-allocated array (no heap allocation needed)
 */
void getSecretNum(char *secretNum) {
    /*
     * Create array of available digits
     * Initialized with digits '0' through '9' as characters
     * Using char array because we're building a string, not doing math
     */
    char numbers[] = "0123456789";
    int numCount = 10;  // Total number of available digits

    /*
     * Fisher-Yates shuffle algorithm
     * Randomly shuffles the array in-place
     * More efficient than Python's random.shuffle but same concept
     */
    int i;  // Loop counter - declared here for C89/C90 compatibility
    for (i = numCount - 1; i > 0; i--) {
        /*
         * rand() returns pseudo-random int from 0 to RAND_MAX
         * Modulo (%) gives us a number from 0 to i (inclusive)
         * This picks a random position to swap with
         */
        int j = rand() % (i + 1);

        /*
         * Swap elements at positions i and j
         * Using temporary variable temp (classic swap algorithm)
         */
        char temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    /*
     * Build the secret number string
     * Take first NUM_DIGITS characters from shuffled array
     */
    for (i = 0; i < NUM_DIGITS; i++) {
        secretNum[i] = numbers[i];  // Copy each digit
    }

    /*
     * Null-terminate the string
     * CRITICAL: All C strings must end with '\0'
     * Without this, string functions won't know where the string ends
     */
    secretNum[NUM_DIGITS] = '\0';
}

/*
 * Function: getClues
 * Generates clue string based on guess and secret number
 *
 * Parameters:
 *   const char *guess - Player's guess (const = we won't modify it)
 *   const char *secretNum - The secret number (const = read-only)
 *   char *result - Output buffer where clue string will be written
 *
 * The const keyword is a promise that we won't modify those strings
 */
void getClues(const char *guess, const char *secretNum, char *result) {
    // Check for exact match first
    if (strcmp(guess, secretNum) == 0) {
        strcpy(result, "You got it!");
        return;  // Early return - no need to generate clues
    }

    /*
     * Arrays to track Fermi and Pico clues
     * We'll count them, then build the result string
     * This approach is more efficient than building strings incrementally
     */
    int fermiCount = 0;
    int picoCount = 0;

    /*
     * First pass: Check each position for exact matches (Fermi)
     * Loop through each digit position
     */
    int i;
    for (i = 0; i < NUM_DIGITS; i++) {
        if (guess[i] == secretNum[i]) {
            fermiCount++;  // Correct digit in correct position
        }
    }

    /*
     * Second pass: Check for correct digits in wrong positions (Pico)
     * Nested loop to check if each guess digit exists elsewhere in secret
     */
    for (i = 0; i < NUM_DIGITS; i++) {
        // Skip if this position already counted as Fermi
        if (guess[i] == secretNum[i]) {
            continue;
        }

        // Check if this digit exists anywhere in the secret number
        int j;
        for (j = 0; j < NUM_DIGITS; j++) {
            // Found the digit in a different position
            if (guess[i] == secretNum[j] && i != j) {
                picoCount++;
                break;  // Count each digit only once
            }
        }
    }

    /*
     * Build result string based on counts
     * Using result[0] = '\0' to initialize as empty string
     */
    result[0] = '\0';

    // No correct digits at all
    if (fermiCount == 0 && picoCount == 0) {
        strcpy(result, "Bagels");
        return;
    }

    /*
     * Build clue string in alphabetical order (Fermi before Pico)
     * This prevents giving away positional information
     * Using strcat to concatenate strings
     */

    // Add "Fermi" for each exact match
    for (i = 0; i < fermiCount; i++) {
        /*
         * strcat: String concatenation
         * Appends source string to destination
         * Automatically handles null terminator
         */
        if (strlen(result) > 0) {
            strcat(result, " ");  // Add space between clues
        }
        strcat(result, "Fermi");
    }

    // Add "Pico" for each correct digit in wrong position
    for (i = 0; i < picoCount; i++) {
        if (strlen(result) > 0) {
            strcat(result, " ");
        }
        strcat(result, "Pico");
    }
}

/*
 * Function: isValidGuess
 * Validates that input contains only digit characters
 *
 * Parameters:
 *   const char *guess - String to validate
 *
 * Returns:
 *   int - 1 (true) if all characters are digits, 0 (false) otherwise
 *   C doesn't have a boolean type (until C99), so we use int
 */
int isValidGuess(const char *guess) {
    int i;
    /*
     * Loop through each character in the string
     * strlen returns the length (excluding '\0')
     */
    for (i = 0; i < strlen(guess); i++) {
        /*
         * isdigit: Checks if character is a decimal digit (0-9)
         * Returns non-zero if true, 0 if false
         * The ! operator negates it - if NOT a digit, return false
         */
        if (!isdigit((unsigned char)guess[i])) {
            return 0;  // Found non-digit character - invalid
        }
    }
    return 1;  // All characters are digits - valid
}

/*
 * Function: clearInputBuffer
 * Clears any remaining characters in stdin buffer
 * Useful after scanf to prevent input issues
 * Not used in current implementation but included for completeness
 */
void clearInputBuffer(void) {
    int c;
    /*
     * Read and discard characters until newline or EOF
     * getchar() reads one character from stdin
     */
    while ((c = getchar()) != '\n' && c != EOF);
}
