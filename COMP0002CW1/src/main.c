#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "maze.h"
#include "robot.h"
#include "maze_gen.h"

#define MOVE_DELAY_MS 100

#define WIDTH 600
#define HEIGHT 360

// traverse one step using a right hand wall following algorithm
static void stepWallFollower(struct Robot *robot, const struct Maze *maze){
    right(robot);
    
    while(!canMoveForward(robot,maze)){
        left(robot);
    }
    forward(robot,maze);
}

static void findExit(struct Robot *robot, const struct Maze *maze){
    int stillSearching = 1;
    while(stillSearching){
        clear();
        drawRobot(robot,maze);

        // traverse the maze, step by step
        if(atMarker(robot,maze)){
            stillSearching = 0;
        }else{
            stepWallFollower(robot,maze);
        }

        sleep(MOVE_DELAY_MS);
    }
}

// can add cli arguments initialX, initialY, direction facing (0,1,2,3=N,E,S,W)
int main(void){
    // taken from chatGPT. uses time to seed random
    srand((unsigned int)time(NULL));

    setWindowSize(WIDTH,HEIGHT);
    struct Maze maze;
    // set default start pos and direction of robot
    struct Robot robot = {.pos={0,1}, .facing=EAST};

    initMaze(&maze, (struct Point){WIDTH,HEIGHT});
    // keep entrance to maze as robots initial position for simplicity, can be changed
    genMaze(&maze, robot.pos);
    drawMaze(&maze);

    foreground();
    setColour(magenta);     // robot colour

    findExit(&robot, &maze);

    return 0;
}