#ifndef MAZE_H
#define MAZE_H

#include "utils.h"

#define ROWS 19
#define COLS 19

enum Tiles{
    EMPTY,
    WALL,
    EXIT
};

struct Maze{
    int tiles[ROWS][COLS];
    int tileWidth;
};

void initMaze(struct Maze *maze, struct Point windowSize);
void drawMaze(struct Maze *maze);

#endif