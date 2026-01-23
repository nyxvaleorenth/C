#include <stdio.h>      // printf, putchar
#include <stdlib.h>     // rand, srand, system, exit
#include <string.h>     // memcpy
#include <threads.h>
#include <time.h>       // time (seeding random)
#include <signal.h>     // signal, SIGINT for Ctrl-C
#include <unistd.h>     // sleep

#define WIDTH 79
#define HEIGHT 20

#define ALIVE '#'
#define DEAD ' '

char cells[HEIGHT][WIDTH];
char nextCells[HEIGHT][WIDTH];

volatile sig_atomic_t shouldExit = 0;

void initializeGrid(void);
void printGrid(void);
void calculateNextGeneration(void);
void copyGrid(void);
void handleSignal(int signal);
void clearScreen(void);


int main(void) {
    srand(time(NULL));

    signal(SIGINT, handleSignal);

    initializeGrid();

    while (!shouldExit) {
        clearScreen();

        copyGrid();

        printGrid();

        calculateNextGeneration();

        sleep(1);
    }

    printf("Conway's Game of Life\n");

    return 0;
}

void initializeGrid(void) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (rand() % 2 == 0) {
                nextCells[y][x] = ALIVE;
            } else {
                nextCells[y][x] = DEAD;
            }
        }
    }
}

void printGrid(void) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(cells[y][x]);
        }
        putchar('\n');
    }
    printf("Press Ctrl-C to quit.\n");
}

void calculateNextGeneration(void) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int left = (x - 1 + WIDTH) % WIDTH;
            int right = (x + 1) % WIDTH;
            int above = (y - 1 + HEIGHT) % HEIGHT;
            int below = (y + 1) % HEIGHT;

            int numNeighbors = 0;

            if (cells[above][left] == ALIVE) {
                numNeighbors++;
            }

            if (cells[above][x]) {
                numNeighbors++;
            }

            if (cells[above][right] == ALIVE) {
                numNeighbors++;
            }

            if (cells[y][left] == ALIVE) {
                numNeighbors++;
            }

            if (cells[y][right] == ALIVE) {
                numNeighbors++;
            }

            if (cells[below][left] == ALIVE) {
                numNeighbors++;
            }

            if (cells[below][x] == ALIVE) {
                numNeighbors++;
            }

            if (cells[below][right] == ALIVE) {
                numNeighbors++;
            }

            if (cells[y][x] == ALIVE && (numNeighbors == 2 || numNeighbors == 3)) {
                nextCells[y][x] = ALIVE;
            }
            else if (cells[y][x] == DEAD && numNeighbors == 3) {
                nextCells[y][x] = ALIVE;
            }
            else {
                nextCells[y][x] = DEAD;
            }
        }
    }
}

void copyGrid(void) {
    memcpy(cells, nextCells, sizeof(cells));
}

void handleSignal(int signal) {
    shouldExit = 1;
}

void clearScreen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}
