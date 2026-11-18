#ifndef ROBOT_H
#define ROBOT_H

#include "utils.h"
#include "maze.h"

#define VERTICES 3

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

int canMoveForward(const struct Robot *robot, const struct Maze *maze);

// CONTROL METHODS
void forward(struct Robot *robot, const struct Maze *maze);
void left(struct Robot *robot);
void right(struct Robot *robot);
int atMarker(const struct Robot *robot, const struct Maze *maze);

void drawRobot(const struct Robot *robot, const struct Maze *maze);

#endif