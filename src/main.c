#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "maze.h"
#include "robot.h"
#include "maze_gen.h"

#define WIDTH 600
#define HEIGHT 360

// traverse one step using a right hand wall following algorithm
void stepWallFollower(struct Robot *robot, const struct Maze *maze){
    right(robot);
    
    while(!canMoveForward(robot,maze)){
        left(robot);
    }
    forward(robot,maze);
}



int main(){
    // taken from chatGPT. uses time to seed random
    srand((unsigned int)time(NULL));

    setWindowSize(WIDTH,HEIGHT);
    struct Maze maze;
    struct Robot robot = {.pos={0,1}, .facing=EAST};
    
    
    initMaze(&maze, (struct Point){WIDTH,HEIGHT});
    genMaze(&maze, (struct Point){1,1});
    drawMaze(&maze);
    foreground();
    setColour(magenta);     // robot colour

    int running = 1;
    while(running){
        clear();
        drawRobot(&robot,&maze);

        // traverse the maze, step by step
        if(atMarker(&robot,&maze)){
            running = 0;
        }else{
            stepWallFollower(&robot,&maze);
        }

        sleep(100);
    }
    return 0;
}