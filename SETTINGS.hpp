#pragma once
#include <stdio.h>
#define WIDTH 1920
#define HEIGHT 1080
#define BITSPERPIXEL 32
#define FULLSCREEN 1
#define RESOURCE_FONT_SIZE 35
#define CELL_SIZE 110
#define GRID_OFFSET 120
#define LEFT_OFFSET 5
#define TOP_OFFSET 140
#if WIDTH==1920 && HEIGHT == 1080
inline void print_size() { printf("window size: %d,%d\n", WIDTH, HEIGHT); }
#define STRUCTURE_SIZE 100
#define X_OFFSET 0.1012
#define Y_OFFSET 0.35
#endif