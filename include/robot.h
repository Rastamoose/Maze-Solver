#ifndef ROBOT_H
#define ROBOT_H

#include "utils.h"
#include "maze.h"
#include "graphics.h"

enum Direction{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct Robot{
    struct Point pos;
    struct Point nextPos;
    enum Direction facing;
};

void updateNextPos(struct Robot *robot);
int canMoveForward(struct Robot *robot, const struct Maze *maze);

// CONTROL METHODS
void forward(struct Robot *robot, const struct Maze *maze);
void left(struct Robot *robot);
void right(struct Robot *robot);
int atMarker(struct Robot *robot, const struct Maze *maze);

void drawRobot(const struct Robot *robot, const struct Maze *maze);

#endif