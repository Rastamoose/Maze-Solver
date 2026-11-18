#include "maze_gen.h"
#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

/* start at a cell. add this to visited
    pick a neighbour from random
    go to that neighbour and add that to active + visited
    repeat until youre on a cell with no available neighbours
    remove this cell from the active list
    go to the last cell in active and repeat until no cells left in active
*/


static int cellOutOfBounds(struct Point pos){
    return (pos.x<=0 || pos.x>=COLS-1 ||
            pos.y<=0 || pos.y>=ROWS-1);
}

static int getUnvisitedNeighbours(int visited[][COLS], struct Point curr, struct Point neighbours[4]){
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

// using a growing tree algorithm. currently operates as recursive backtracker
// chatgpt used to refine pseudocode/plans. NOT used to code method
void genMaze(int maze[][COLS], const struct Point startPos){
    int visited[ROWS][COLS] = {0};
    struct Point active[ROWS*COLS];
    int activeCount = 0;
    
    struct Point curr = startPos;
    maze[curr.y][curr.x] = EMPTY;
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
            maze[next.y][next.x]=EMPTY;
            maze[(curr.y+next.y)/2][(curr.x+next.x)/2] = EMPTY;
            // now update visited and active
            visited[next.y][next.x]=1;
            active[activeCount++]=next;
        // if there are no neighbours then go to the previous active cell
        }else{
            activeCount--;
        }
    }

    // open up {0,1}
    maze[1][0] = EMPTY;
}
