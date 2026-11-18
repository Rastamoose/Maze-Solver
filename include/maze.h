#ifndef MAZE_H
#define MAZE_H

#include "utils.h"

#define MAZE_ROWS 19
#define MAZE_COLS 19

enum Tiles{
    EMPTY,
    WALL,
    EXIT
};

struct Maze{
    int tiles[MAZE_ROWS][MAZE_COLS];
    int tileLength;
};

void initMaze(struct Maze *maze, struct Point windowSize);
void drawMaze(const struct Maze *maze);

#endif