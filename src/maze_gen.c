#include "maze_gen.h"
#include "maze.h"
#include <stdlib.h>

/* start at a cell. add this to visited
    pick a neighbour from random
    go to that neighbour and add that to active + visited
    repeat until youre on a cell with no available neighbours
    remove this cell from the active list
    go to the last cell in active and repeat until no cells left in active
*/


static int cellOutOfBounds(struct Point pos){
    return (pos.x<=0 || pos.x>=MAZE_COLS-1 ||
            pos.y<=0 || pos.y>=MAZE_ROWS-1);
}

static int getUnvisitedNeighbours(int visited[][MAZE_COLS], struct Point curr, struct Point neighbours[4]){
    struct Point candidates[4] = {
        {curr.x,curr.y-2},    // NORTH
        {curr.x+2,curr.y},    // EAST
        {curr.x,curr.y+2},    // SOUTH
        {curr.x-2,curr.y}     // WEST
    };

    int count = 0;
    // a valid neighbour must be within bounds and not visited yet
    for(int i=0;i<4;i++){
        struct Point next = candidates[i];

        if(cellOutOfBounds(next)){
            continue;
        }

        if(!visited[next.y][next.x]){
            neighbours[count] = next;
            count++;
        }
    }
    return count;
}

// open an exit along the bottom or right edge of the maze
static void openExit(struct Maze *maze){
    // num of options is one row + one col (minus the borders)
    struct Point options[(MAZE_ROWS-2)+(MAZE_COLS-2)];
    int count = 0;
    // get bottom edge
    for(int col=1;col<(MAZE_COLS-1);col++){
        if(maze->tiles[MAZE_ROWS-2][col]==EMPTY){
            // the actual option will be on the border so -1 instead of -2
            options[count++] = (struct Point){col,MAZE_ROWS-1};
        }
    }

    // get right edge
    for(int row=1;row<(MAZE_ROWS-1);row++){
        if(maze->tiles[row][MAZE_COLS-2]==EMPTY){
            options[count++] = (struct Point){MAZE_COLS-1,row};
        }
    }

    struct Point selected = options[rand()%count];
    maze->tiles[selected.y][selected.x]=EXIT;
}

// using a growing tree algorithm. currently operates as recursive backtracker
// chatgpt used to refine pseudocode/plans. NOT used to code method
void genMaze(struct Maze *maze, struct Point startPos){
    int visited[MAZE_ROWS][MAZE_COLS] = {0};
    struct Point active[MAZE_ROWS*MAZE_COLS];
    int activeCount = 0;
    
    struct Point curr = startPos;
    maze->tiles[curr.y][curr.x] = EMPTY;
    visited[curr.y][curr.x] = 1;
    active[activeCount++] = curr;
    struct Point neighbours[4];

    // while the active array is still populated
    while(activeCount>0){
        curr = active[activeCount-1];
        int count = getUnvisitedNeighbours(visited, curr, neighbours);
        // pick a random neighbour to be the next cell
        if(count>0){
            struct Point next = neighbours[rand()%count];
            // open that cell up, and the barrier between them
            maze->tiles[next.y][next.x]=EMPTY;
            maze->tiles[(curr.y+next.y)/2][(curr.x+next.x)/2] = EMPTY;
            // now update visited and active
            visited[next.y][next.x]=1;
            active[activeCount++]=next;
        // if there are no neighbours then go to the previous active cell
        }else{
            activeCount--;
        }
    }

    // open up start point
    maze->tiles[startPos.y][startPos.x] = EMPTY;
    openExit(maze);
}
