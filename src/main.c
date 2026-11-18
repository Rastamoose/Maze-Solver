#include <stdio.h>
#include <stdlib.h>
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

// fill maze with walls
void initBlankMaze(int maze[][COLS], int rows, int cols){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            maze[i][j]=WALL;
        }
    }

}

int main(void){
    setWindowSize(WIDTH,HEIGHT);
    // struct Maze maze = {
    //     .tiles = {
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    //     {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,0,1},
    //     {1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
    //     {1,0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,0,1},
    //     {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1},
    //     {1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,0,1},
    //     {1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1},
    //     {1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1},
    //     {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
    //     {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
    //     {1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,0,1},
    //     {1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
    //     {1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1}
    //     }
    //};

    struct Maze maze;
    
    struct Robot robot = {.pos={0,1}, .facing=EAST};
    
    
    initBlankMaze(maze.tiles, ROWS,COLS);
    genMaze(maze.tiles, (struct Point){10,10});
    initMaze(&maze, (struct Point){WIDTH,HEIGHT});
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