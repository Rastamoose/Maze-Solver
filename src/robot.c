#include "robot.h"
#include "maze.h"
#include "utils.h"
#include "graphics.h"

// relative vertices of traingles facing different directions
static const struct Pointf tris[4][3] = {
    [NORTH] = {{0.5,0},{0,1},{1,1}},
    [EAST] = {{0,0},{1,0.5},{0,1}},
    [SOUTH] = {{0,0},{1,0},{0.5,1}},
    [WEST] = {{0,0.5},{1,0},{1,1}}
};

static void updateNextPos(struct Robot *robot){
    robot->nextPos.x = robot->pos.x;
    robot->nextPos.y = robot->pos.y;

    switch (robot->facing){
        case NORTH: robot->nextPos.y--;    break;
        case EAST:  robot->nextPos.x++;    break;
        case SOUTH: robot->nextPos.y++;    break;
        case WEST:  robot->nextPos.x--;    break;
    }
}

int canMoveForward(struct Robot *robot, const struct Maze *maze){
    updateNextPos(robot);
    // bounds checking
    if(robot->nextPos.x<0 || robot->nextPos.x>=COLS ||
       robot->nextPos.y<0 || robot->nextPos.y>=ROWS){
        return 0;
       }

    return maze->tiles[robot->nextPos.y][robot->nextPos.x]!=WALL;
}

void forward(struct Robot *robot, const struct Maze *maze){
    // canMoveForward will updateNextPos so we dont need to repeat that call
    if(canMoveForward(robot,maze)){
        robot->pos.x = robot->nextPos.x;
        robot->pos.y = robot->nextPos.y;
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
    int vertices = 3;
    int xCoords[3];
    int yCoords[3];

    
    // compute window position for each vertex based on robot pos + relative offset 
    for(int i=0;i<vertices;i++){
        xCoords[i] = (robot->pos.x+tris[robot->facing][i].x)*(maze->tileWidth);
        yCoords[i] = (robot->pos.y+tris[robot->facing][i].y)*(maze->tileWidth);
    }

    fillPolygon(3,xCoords,yCoords);
}
