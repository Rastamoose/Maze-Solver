#include "maze.h"
#include "graphics.h"
#include "utils.h"

void initMaze(struct Maze *maze, struct Point windowSize){
    // fill maze with walls
    for(int row=0;row<MAZE_ROWS;row++){
        for(int col=0;col<MAZE_COLS;col++){
            maze->tiles[row][col]=WALL;
        }
    }
    
    // tiles are square, so we want to use smaller of width, height
    int tileWidth = windowSize.x/MAZE_COLS;
    int tileHeight = windowSize.y/MAZE_ROWS;
 
    maze->tileLength = tileWidth<tileHeight ? tileWidth:tileHeight;
}

static void drawTile(const struct Maze *maze, struct Point tileIndex){
    int tileVal = maze->tiles[tileIndex.y][tileIndex.x];
    struct Point pixelPos = {maze->tileLength*tileIndex.x,maze->tileLength*tileIndex.y};

    switch (tileVal){
        case EMPTY:
            // if empty tile we'll just skip rendering
            return;
        case WALL:
            setColour(black);
            break;
        case EXIT:
            setColour(green);
    }

    fillRect(pixelPos.x,pixelPos.y,maze->tileLength,maze->tileLength);
}

static void drawRowLine(const struct Maze *maze, int rowNum){
    int rowYPos = maze->tileLength*rowNum;
    drawLine(0,rowYPos,maze->tileLength*MAZE_COLS-1,rowYPos);   // -1 added to prevent line sticking out
}

static void drawRowCol(const struct Maze *maze, int colNum){
    int colXPos = maze->tileLength*colNum;
    drawLine(colXPos,0,colXPos,maze->tileLength*MAZE_ROWS-1);
}

void drawMaze(const struct Maze *maze){
    background();

    for(int row=0;row<MAZE_ROWS;row++){
        drawRowLine(maze,row);
        for(int col=0;col<MAZE_COLS;col++){
            // only render cols on first pass of rows
            if(row==0)  drawRowCol(maze,col);
            drawTile(maze,(struct Point){col,row});
        }
    }   
}