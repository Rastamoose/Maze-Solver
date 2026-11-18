#include "robot.h"
#include "maze.h"
#include "utils.h"
#include "graphics.h"

// relative vertices of traingles facing different directions
static const struct Pointf tris[4][VERTICES] = {
    [NORTH] = {{0.5,0},{0,1},{1,1}},
    [EAST] = {{0,0},{1,0.5},{0,1}},
    [SOUTH] = {{0,0},{1,0},{0.5,1}},
    [WEST] = {{0,0.5},{1,0},{1,1}}
};

static struct Point getNextPos(const struct Robot *robot){
    struct Point nextPos = robot->pos;

    switch (robot->facing){
        case NORTH: nextPos.y--;    break;
        case EAST:  nextPos.x++;    break;
        case SOUTH: nextPos.y++;    break;
        case WEST:  nextPos.x--;    break;
    }
    return nextPos;
}

int canMoveForward(const struct Robot *robot, const struct Maze *maze){
    struct Point nextPos = getNextPos(robot);
    // bounds checking
    if(nextPos.x<0 || nextPos.x>=MAZE_COLS ||
       nextPos.y<0 || nextPos.y>=MAZE_ROWS){
        return 0;
    }

    return maze->tiles[nextPos.y][nextPos.x]!=WALL;
}

void forward(struct Robot *robot, const struct Maze *maze){
    // canMoveForward will updateNextPos so we dont need to repeat that call
    struct Point nextPos = getNextPos(robot);
    if(canMoveForward(robot,maze)){
        robot->pos.x = nextPos.x;
        robot->pos.y = nextPos.y;
    }
}

// robot direction is an enum so we can +1 or -1 to change direction, staying within range 0-3
void left(struct Robot *robot){
    // +3 instead of -1 to avoid negative numbers
    robot->facing = ((robot->facing)+3)%4;
}

void right(struct Robot *robot){
    robot->facing = ((robot->facing)+1)%4;
}

int atMarker(const struct Robot *robot, const struct Maze *maze){
    return maze->tiles[robot->pos.y][robot->pos.x]==EXIT;
}

void drawRobot(const struct Robot *robot, const struct Maze *maze){
    int xCoords[VERTICES];
    int yCoords[VERTICES];

    
    // compute window position for each vertex based on robot pos + relative offset 
    for(int i=0;i<VERTICES;i++){
        xCoords[i] = (robot->pos.x+tris[robot->facing][i].x)*(maze->tileWidth);
        yCoords[i] = (robot->pos.y+tris[robot->facing][i].y)*(maze->tileWidth);
    }

    fillPolygon(VERTICES,xCoords,yCoords);
}
