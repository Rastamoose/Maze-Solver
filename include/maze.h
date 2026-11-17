#ifndef MAZE_H
#define MAZE_H

#include "utils.h"

#define ROWS 18
#define COLS 18

struct Maze{
    int tiles[ROWS][COLS];
};

int getTileSize(struct Point windowSize);
void drawTile(int tileVal, struct Point pos, int tileWidth);
void drawMaze(const struct Maze *maze, struct Point windowSize);

#endif