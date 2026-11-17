#include "maze.h"
#include "graphics.h"
#include "utils.h"

// return width/height of tiles given grid size and window size (tiles are square)
int getTileSize(struct Point windowSize){
    int width = windowSize.x/COLS;
    int height = windowSize.y/ROWS;
 
    // we want to return the smaller side, so the full grid fits in the window
    return width<height ? width:height;
}

void drawTile(int tileVal, struct Point pos, int tileWidth){
    switch (tileVal){
        case 0:
            // if empty tile we'll just skip rendering
            return;
        case 1:
            setColour(black);
            break;
        case 2:
            setColour(green);
    }

    fillRect(pos.x,pos.y,tileWidth,tileWidth);
    setColour(black);
}

void drawMaze(const struct Maze *maze, struct Point windowSize){
    background();
    int tileWidth = getTileSize(windowSize);

    for(int i=0;i<ROWS;i++){
        // render the horizontal gridline for this row
        int rowYPos = tileWidth*i;
        drawLine(0,rowYPos,tileWidth*COLS-1,rowYPos);   // -1 added to prevent line sticking out
        for(int j=0;j<COLS;j++){
            // render the vertical gridline for this col
            int colXPos = tileWidth*j;
            drawLine(colXPos,0,colXPos,tileWidth*ROWS-1);

            struct Point pos = {tileWidth*j,tileWidth*i};
            drawTile(maze->tiles[i][j],pos,tileWidth);
        }
    }
}