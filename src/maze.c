#include "maze.h"
#include "graphics.h"
#include "utils.h"

void initMaze(struct Maze *maze, struct Point windowSize){
    // get width/height of tiles given grid size and window size (tiles are square)
    int width = windowSize.x/COLS;
    int height = windowSize.y/ROWS;
 
    // we want to use the smaller side, so the full grid fits in the window
    maze->tileWidth = width<height ? width:height;
}

static void drawTile(struct Maze *maze, struct Point tileIndex){
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

void drawMaze(struct Maze *maze){
    background();

    for(int i=0;i<ROWS;i++){
        // render the horizontal gridline for this row
        int rowYPos = maze->tileWidth*i;
        drawLine(0,rowYPos,maze->tileWidth*COLS-1,rowYPos);   // -1 added to prevent line sticking out
        for(int j=0;j<COLS;j++){
            // render the vertical gridline for this col (but only on the first pass)
            if(i==0){
                int colXPos = maze->tileWidth*j;
                drawLine(colXPos,0,colXPos,maze->tileWidth*ROWS-1);
            } 
            drawTile(maze,(struct Point){j,i});
        }
    }
    
    foreground();
}