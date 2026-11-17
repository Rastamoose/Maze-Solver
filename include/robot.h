#ifndef ROBOT_H
#define ROBOT_H

#include "utils.h"
#include "maze.h"

enum Direction{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct Robot{
    struct Point pos;
    enum Direction facing;
};

int canMoveForward(const struct Maze *maze);
void forward(struct Robot *robot, const struct Maze *maze);
void left(void);
void right(void);
int atMarker(void);

#endif