#include "maze.h"
#include "graphics.h"
#include "utils.h"

void initMaze(struct Maze *maze, struct Point windowSize){
    // fill maze with walls
    for(int i=0;i<MAZE_ROWS;i++){
        for(int j=0;j<MAZE_COLS;j++){
            maze->tiles[i][j]=WALL;
        }
    }
    
    // get width/height of tiles given grid size and window size (tiles are square)
    int width = windowSize.x/MAZE_COLS;
    int height = windowSize.y/MAZE_ROWS;
 
    // we want to use the smaller side, so the full grid fits in the window
    maze->tileWidth = width<height ? width:height;
}

static void drawTile(const struct Maze *maze, struct Point tileIndex){
    int tileVal = maze->tiles[tileIndex.y][tileIndex.x];
    // real window position of tile
    struct Point realPos = {maze->tileWidth*tileIndex.x,maze->tileWidth*tileIndex.y};

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

    fillRect(realPos.x,realPos.y,maze->tileWidth,maze->tileWidth);
    setColour(black);
}

void drawMaze(const struct Maze *maze){
    background();

    for(int row=0;row<MAZE_ROWS;row++){
        // render the horizontal gridline for this row
        int rowYPos = maze->tileWidth*row;
        drawLine(0,rowYPos,maze->tileWidth*MAZE_COLS-1,rowYPos);   // -1 added to prevent line sticking out
        for(int col=0;col<MAZE_COLS;col++){
            // render the vertical gridline for this col (but only on the first pass)
            if(row==0){
                int colXPos = maze->tileWidth*col;
                drawLine(colXPos,0,colXPos,maze->tileWidth*MAZE_ROWS-1);
            } 
            drawTile(maze,(struct Point){col,row});
        }
    }   
}