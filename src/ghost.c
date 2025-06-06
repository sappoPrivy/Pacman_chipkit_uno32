/*bitmaps.c
	Created by Tenzin Sangpo Choedon
*/
#include <stdint.h>   
#include <pic32mx.h>
#include "functions.h"  


void init_ghost(Ghost *ghost, Coord coord){
    // Ghost graphic is the basic
	ghost->graphic = ghost_basic;

    // Ghost is spawned
	copy_coordinate(&ghost->position, coord);

    // Ghost is alive
	ghost->ghost_state = 1;

    // Generates a random direction
    ghost->randomDirection = rand() % 4;

    // Generates a random number of steps
    ghost->randomSteps = rand() % 6;
}

/* Draw ghost at a new position */
void draw_ghost(Ghost *ghost){
	int y, x;

	for(y = 0; y < SIZE_OF_GHOST; ++y)
	{
		for(x = 0; x < SIZE_OF_GHOST; ++x)
		{
			display_set(x - 2 + ghost->position.x, y -2 + ghost->position.y, ghost->graphic[y*SIZE_OF_GHOST + x]);
		}
	}
}


/* Check new position is valid*/ 
int valid_ghost_position(Ghost *ghost, int x, int y){ 

    // Check if the new position is inacessable 
    if(get_pixelData(&(Coord){ghost->position.x + x, ghost->position.y + y}) & INACCESSIBLE) 
        return 0; 
    
	// Otherwise the position is valid 
    return 1; 

} 

void move_ghost(Ghost *ghost){
    int i;
    bool findDirection = false;

    /* Loop until the ghost finds an accessible direction*/
    while(!findDirection){

        /* Move right */
        if(ghost->randomDirection == 0 && valid_ghost_position(ghost, 1, 0)){ 
            mod_coordinate(&ghost->position, 1, 0);
            findDirection = true;
            ghost->randomSteps--;
        }     

        /* Move down */ 
        if(ghost->randomDirection == 1 && valid_ghost_position(ghost, 0, 1)){ 
            mod_coordinate(&ghost->position, 0, 1);
            findDirection = true;
            ghost->randomSteps--;
        } 

        /* Move up */ 
        if(ghost->randomDirection == 2 && valid_ghost_position(ghost, 0, -1)){ 
            mod_coordinate(&ghost->position, 0, -1); 
            findDirection = true;
            ghost->randomSteps--;
        } 

        /* Move left */ 
        if(ghost->randomDirection == 3 && valid_ghost_position(ghost, -1, 0)){ 
            mod_coordinate(&ghost->position, -1, 0); 
            findDirection = true;
            ghost->randomSteps--;
        } 
    
        /* The direction is not accessible or steps are finished*/
        if(!findDirection || ghost->randomSteps == 0){
            // New direction
            ghost->randomDirection = rand() % 4;
            // New number of steps
            ghost->randomSteps = rand() % 6;
        }

        /* Otherwise continue to loop random number of steps in that direction*/

    }

    
}