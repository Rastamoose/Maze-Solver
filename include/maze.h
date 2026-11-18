#ifndef MAZE_H
#define MAZE_H

#include "utils.h"

#define ROWS 18
#define COLS 18

struct Maze{
    int tiles[ROWS][COLS];
    int tileWidth;
};

void initMaze(struct Maze *maze, struct Point windowSize);

void drawTile(struct Maze *maze, struct Point tileIndex);
void drawMaze(struct Maze *maze);

#endif