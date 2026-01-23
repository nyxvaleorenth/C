/*
 * Conway's Game of Life - C Implementation
 * The classic cellular automata simulation. Press Ctrl-C to stop.
 * More info at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 * Converted to C from Python original by Al Sweigart
 */

#include <stdio.h>      // Standard I/O functions: printf, putchar
#include <stdlib.h>     // Standard library: rand, srand, system, exit
#include <string.h>     // String functions: memcpy
#include <time.h>       // Time functions: time (for seeding random)
#include <signal.h>     // Signal handling: signal, SIGINT (for Ctrl-C)
#include <unistd.h>     // POSIX functions: sleep

// ============================================================================
// CONSTANTS
// ============================================================================

// Grid dimensions - these define the simulation space
#define WIDTH 79        // Number of cells horizontally (fits terminal width)
#define HEIGHT 20       // Number of cells vertically

// Character representations for cells
// Note: In C, we use char to represent single characters
// The Python version used Unicode block character "█", but for portability
// we'll use '#' for alive and ' ' (space) for dead
#define ALIVE '#'       // Living cell representation
#define DEAD ' '        // Dead cell representation

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// The game state is stored in a 2D character array
// In C, we use static arrays allocated on the stack for simplicity
// cells[y][x] gives us the cell at position (x, y)
// We store by [y][x] (row-major order) which is more cache-friendly in C
char cells[HEIGHT][WIDTH];      // Current generation
char nextCells[HEIGHT][WIDTH];  // Next generation being calculated

// Flag to track if we should exit (set by signal handler)
volatile sig_atomic_t shouldExit = 0;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

void initializeGrid(void);
void printGrid(void);
void calculateNextGeneration(void);
void copyGrid(void);
void handleSignal(int signal);
void clearScreen(void);

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    // Seed the random number generator with current time
    // time(NULL) returns seconds since Unix epoch (Jan 1, 1970)
    // This ensures different random patterns each run
    srand(time(NULL));

    // Set up signal handler for graceful exit on Ctrl-C (SIGINT)
    // signal() registers a function to be called when a signal is received
    signal(SIGINT, handleSignal);

    // Initialize the grid with random alive/dead cells
    initializeGrid();

    // Main simulation loop - runs indefinitely until Ctrl-C
    while (!shouldExit) {
        // Clear the screen for the new frame
        clearScreen();

        // Copy nextCells to cells for this generation
        // We need to do this because we calculate the next generation
        // based on the current one
        copyGrid();

        // Display the current state of the simulation
        printGrid();

        // Compute what the next generation will look like
        // based on Conway's rules
        calculateNextGeneration();

        // Pause for 1 second to make the animation visible
        // sleep() is a POSIX function that suspends execution
        sleep(1);
    }

    // Print exit message
    printf("\nConway's Game of Life\n");
    printf("C implementation based on original by Al Sweigart\n");

    // Return 0 to indicate successful execution
    // This is the standard way to exit a C program normally
    return 0;
}

// ============================================================================
// FUNCTION IMPLEMENTATIONS
// ============================================================================

/*
 * initializeGrid - Initialize the grid with random alive/dead cells
 *
 * This function loops through every position in the grid and randomly
 * sets each cell to either ALIVE or DEAD with 50% probability.
 */
void initializeGrid(void) {
    // Loop through each row (y coordinate)
    for (int y = 0; y < HEIGHT; y++) {
        // Loop through each column (x coordinate)
        for (int x = 0; x < WIDTH; x++) {
            // rand() returns a pseudo-random integer
            // rand() % 2 gives us either 0 or 1 (50/50 chance)
            // We use this to randomly set cells to alive or dead
            if (rand() % 2 == 0) {
                nextCells[y][x] = ALIVE;
            } else {
                nextCells[y][x] = DEAD;
            }
        }
    }
}

/*
 * printGrid - Display the current grid state to the console
 *
 * Prints each cell character followed by a newline at the end of each row.
 */
void printGrid(void) {
    // Iterate through each row
    for (int y = 0; y < HEIGHT; y++) {
        // Iterate through each column in this row
        for (int x = 0; x < WIDTH; x++) {
            // putchar() outputs a single character to stdout
            // It's more efficient than printf() for single characters
            putchar(cells[y][x]);
        }
        // Print newline at end of row to move to next line
        // putchar('\n') is equivalent to printf("\n")
        putchar('\n');
    }
    // Print instructions for the user
    printf("Press Ctrl-C to quit.\n");
}

/*
 * calculateNextGeneration - Apply Conway's Game of Life rules
 *
 * Conway's Rules:
 * 1. Any live cell with 2 or 3 live neighbors survives
 * 2. Any dead cell with exactly 3 live neighbors becomes alive
 * 3. All other cells die or remain dead
 *
 * This function examines each cell and its 8 neighbors to determine
 * the cell's state in the next generation.
 */
void calculateNextGeneration(void) {
    // Loop through every cell in the grid
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Calculate neighbor coordinates with wraparound (toroidal topology)
            // The modulo operator (%) ensures coordinates wrap around the edges
            // Example: if x=0, then left=(0-1)%WIDTH = WIDTH-1 (rightmost column)
            int left = (x - 1 + WIDTH) % WIDTH;   // Column to the left
            int right = (x + 1) % WIDTH;          // Column to the right
            int above = (y - 1 + HEIGHT) % HEIGHT; // Row above
            int below = (y + 1) % HEIGHT;         // Row below

            // Count living neighbors among the 8 surrounding cells
            // We check each of the 8 positions around (x, y)
            int numNeighbors = 0;

            // Top-left neighbor
            if (cells[above][left] == ALIVE) {
                numNeighbors++;
            }

            // Top neighbor (directly above)
            if (cells[above][x] == ALIVE) {
                numNeighbors++;
            }

            // Top-right neighbor
            if (cells[above][right] == ALIVE) {
                numNeighbors++;
            }

            // Left neighbor (same row)
            if (cells[y][left] == ALIVE) {
                numNeighbors++;
            }

            // Right neighbor (same row)
            if (cells[y][right] == ALIVE) {
                numNeighbors++;
            }

            // Bottom-left neighbor
            if (cells[below][left] == ALIVE) {
                numNeighbors++;
            }

            // Bottom neighbor (directly below)
            if (cells[below][x] == ALIVE) {
                numNeighbors++;
            }

            // Bottom-right neighbor
            if (cells[below][right] == ALIVE) {
                numNeighbors++;
            }

            // Apply Conway's rules to determine next state
            // Rule 1: Living cell with 2 or 3 neighbors survives
            if (cells[y][x] == ALIVE && (numNeighbors == 2 || numNeighbors == 3)) {
                nextCells[y][x] = ALIVE;
            }
            // Rule 2: Dead cell with exactly 3 neighbors becomes alive (reproduction)
            else if (cells[y][x] == DEAD && numNeighbors == 3) {
                nextCells[y][x] = ALIVE;
            }
            // Rule 3: All other cells die or stay dead (overpopulation/underpopulation)
            else {
                nextCells[y][x] = DEAD;
            }
        }
    }
}

/*
 * copyGrid - Copy nextCells array into cells array
 *
 * This prepares the next generation to become the current generation.
 * We use memcpy for efficient memory copying.
 */
void copyGrid(void) {
    // memcpy(destination, source, number_of_bytes)
    // Copies a block of memory from source to destination
    // sizeof(cells) gives us the total size of the 2D array in bytes
    // This is more efficient than nested loops for copying
    memcpy(cells, nextCells, sizeof(cells));
}

/*
 * handleSignal - Signal handler for Ctrl-C (SIGINT)
 *
 * When the user presses Ctrl-C, this function is called.
 * We set a flag to exit gracefully rather than terminating abruptly.
 *
 * Parameters:
 *   signal - The signal number (SIGINT in our case)
 */
void handleSignal(int signal) {
    // Mark that we should exit the main loop
    // volatile sig_atomic_t ensures this write is atomic and visible
    // across signal handlers and main program
    shouldExit = 1;

    // Note: We don't do complex operations here because signal handlers
    // should be kept simple and fast
}

/*
 * clearScreen - Clear the terminal screen
 *
 * This function uses ANSI escape sequences to clear the screen.
 * ANSI escape codes are special character sequences that control
 * terminal behavior.
 */
void clearScreen(void) {
    // Print ANSI escape sequence to clear screen and move cursor to top-left
    // \033 is the ESC character (octal 033 = decimal 27)
    // [2J clears the entire screen
    // [H moves cursor to home position (top-left)
    printf("\033[2J\033[H");

    // Alternative method (less portable but simpler):
    // system("clear");  // On Unix/Linux/Mac
    // system("cls");    // On Windows

    // Flush output buffer to ensure immediate display
    // fflush() forces all buffered output to be written immediately
    fflush(stdout);
}
