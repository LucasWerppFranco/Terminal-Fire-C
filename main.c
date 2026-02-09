#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 100
#define HEIGHT 20

int fire[HEIGHT][WIDTH];

const char *colors[] = {
    "\033[30m",
    "\033[31m",
    "\033[31;1m",
    "\033[33m",
    "\033[33;1m",
    "\033[37m",
    "\033[97m",
    "\033[93m",
    "\033[91m",
    "\033[97;1m"
};

void clear_screen() {
    printf("\033[H\033[J");
}

void init_fire() {
    for (int x = 0; x < WIDTH; x++) {
        fire[HEIGHT - 1][x] = 9;
    }
}

void spread_fire() {
    for (int y = 1; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int decay = rand() % 3;
            int src = fire[y][x];
            int dst = x - (rand() % 3) + 1;

            if (dst < 0) dst = 0;
            if (dst >= WIDTH) dst = WIDTH - 1;

            int new_val = src - decay;
            if (new_val < 0) new_val = 0;

            fire[y - 1][dst] = new_val;
        }
    }
}

void render_fire() {
    clear_screen();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int v = fire[y][x];

            if (v == 0) {
                printf(" ");
            } else {
                printf("%s█", colors[v]);
            }
        }
        printf("\033[0m\n");
    }
}

int main() {
    srand(time(NULL));

    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            fire[y][x] = 0;

    while (1) {
        init_fire();
        spread_fire();
        render_fire();
        usleep(30000);
    }

    return 0;
}

