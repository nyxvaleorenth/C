/*
 * Collatz Sequence, by Al Sweigart al@inventwithpython.com
 * Converted to C by Assistant
 *
 * Generates numbers for the Collatz sequence, given a starting number.
 * More info at: https://en.wikipedia.org/wiki/Collatz_conjecture
 * Tags: tiny, beginner, math
 */

// Standard input/output library - provides printf(), scanf(), fgets()
#include <stdio.h>

// Standard library - provides exit(), atoi(), strtol()
#include <stdlib.h>

// String manipulation library - provides strlen(), strcspn()
#include <string.h>

// Character type checking - provides isdigit()
#include <ctype.h>

// Time/sleep functions - provides nanosleep() on Unix-like systems
#include <time.h>

// Platform-specific: On Windows, we need different sleep function
#ifdef _WIN32
    #include <windows.h>
    // Define a cross-platform sleep function (milliseconds)
    #define SLEEP_MS(ms) Sleep(ms)
#else
    // POSIX systems (Linux, macOS, etc.) use nanosleep
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

/*
 * Function: is_valid_number
 * -------------------------
 * Validates if a string contains only digits (0-9) and represents a positive integer.
 *
 * Parameters:
 *   str - pointer to a null-terminated character array (C string)
 *
 * Returns:
 *   1 (true) if string is all digits and not empty
 *   0 (false) otherwise
 *
 * Note: In C, there's no built-in boolean type (until C99's stdbool.h),
 * so we use int where 0 = false, non-zero = true
 */
int is_valid_number(const char *str) {
    // Check for NULL pointer or empty string
    // str[0] == '\0' checks if first character is the null terminator
    if (str == NULL || str[0] == '\0') {
        return 0;  // Invalid: empty or NULL string
    }

    // Iterate through each character in the string
    // The loop continues until we hit '\0' (null terminator that ends all C strings)
    for (int i = 0; str[i] != '\0'; i++) {
        // isdigit() checks if character is '0'-'9'
        // Returns non-zero if digit, 0 if not
        if (!isdigit((unsigned char)str[i])) {
            return 0;  // Invalid: found non-digit character
        }
    }

    return 1;  // Valid: all characters were digits
}

/*
 * Function: main
 * --------------
 * Entry point of the C program. Unlike Python which starts executing
 * from the top of the file, C always starts at main().
 *
 * Returns:
 *   0 for successful execution
 *   1 for error/invalid input
 */
int main(void) {
    // Character array to store user input
    // Size 100: enough for any reasonable integer input plus newline + null terminator
    // This is allocated on the STACK (automatic storage duration)
    // Memory is automatically freed when function returns
    char input[100];

    // Variable to store the current number in the sequence
    // 'long long' is used instead of 'int' to handle very large numbers
    // that might occur in Collatz sequences (can overflow regular int)
    long long n;

    // printf() - formatted output to stdout (standard output, usually the terminal)
    // Unlike Python's print(), we must explicitly include newline characters (\n)
    printf("Collatz Sequence, or, the 3n + 1 Problem\n");
    printf("By Al Sweigart al@inventwithpython.com\n\n");

    printf("The Collatz sequence is a sequence of numbers produced from a starting\n");
    printf("number n, following three rules:\n\n");
    printf("1) If n is even, the next number n is n / 2.\n");
    printf("2) If n is odd, the next number n is n * 3 + 1.\n");
    printf("3) If n is 1, stop. Otherwise, repeat.\n\n");
    printf("It is generally thought, but so far not mathematically proven, that\n");
    printf("every starting number eventually terminates at 1.\n\n");

    printf("Enter a starting number (greater than 0) or QUIT:\n> ");

    // fgets() - reads a line from stdin into the buffer
    // Parameters: buffer, max size, input stream
    // Unlike Python's input(), fgets() includes the newline character in the result
    // Returns NULL on error or EOF (End Of File)
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;  // Exit with error code
    }

    // Remove the trailing newline that fgets() captures
    // strcspn() returns the length of the initial segment that doesn't contain '\n'
    // Setting that position to '\0' effectively removes the newline
    input[strcspn(input, "\n")] = '\0';

    // Check if user wants to quit
    // strcmp() compares two strings, returns 0 if they're equal
    // In C, strings are just arrays of chars ending with '\0'
    if (strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0) {
        printf("Goodbye!\n");
        return 0;  // Exit successfully
    }

    // Validate that input contains only digits
    if (!is_valid_number(input)) {
        printf("You must enter an integer greater than 0.\n");
        return 1;  // Exit with error code
    }

    // Convert string to long long integer
    // atoll() - ASCII to long long - converts string to number
    // Returns 0 if conversion fails (which we catch with our validation above)
    n = atoll(input);

    // Check if number is valid (greater than 0)
    if (n <= 0) {
        printf("You must enter an integer greater than 0.\n");
        return 1;
    }

    // Print the starting number
    // %lld is the format specifier for long long int
    // Unlike Python's print(n, end="", flush=True), C's printf doesn't
    // automatically flush, so we call fflush() to force output
    printf("%lld", n);
    fflush(stdout);  // Force output to appear immediately

    // Main Collatz sequence loop
    // Continue until n reaches 1
    while (n != 1) {
        // Check if n is even using modulo operator
        // n % 2 gives remainder when dividing by 2
        // If remainder is 0, number is even
        if (n % 2 == 0) {
            // Even: divide by 2
            // Using integer division (automatic in C for integer types)
            n = n / 2;
        } else {
            // Odd: multiply by 3 and add 1
            n = 3 * n + 1;
        }

        // Print the next number with comma separator
        printf(", %lld", n);
        fflush(stdout);  // Force immediate output for visual effect

        // Sleep for 100 milliseconds (0.1 seconds)
        // This creates the "animated" effect of numbers appearing one by one
        SLEEP_MS(100);
    }

    // Print final newline to move to next line after sequence
    printf("\n");

    // Return 0 to indicate successful execution
    // This is the exit code that the operating system receives
    return 0;
}
