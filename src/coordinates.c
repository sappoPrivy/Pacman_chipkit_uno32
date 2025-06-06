/*coordinates.c
	Created by Tenzin Sangpo Choedon
*/
#include <stdint.h>   
#include <pic32mx.h>  
#include "functions.h"

/* Copy coordinates*/
void copy_coordinate(Coord *currentCoord, Coord newCoord){
    currentCoord->x = newCoord.x;
    currentCoord->y = newCoord.y;
}

/*Change coordinates of an existing coordinate*/
void mod_coordinate(Coord *coord, int x, int y){
    coord->x += x;
    coord->y += y;
}

/* Check if the coordinate is valid*/
int valid_coordinate(Coord const *coord){
	if ((coord->x < MP_COLUMNS && coord->x >= 0) && (coord->y < MP_ROWS && coord->y >= 0)){
		return 1;
	}
	else{
		return 0;
	}
}

/* Check if two coordinates are equal*/
int equal_coordinate(Coord const *coordA, Coord const *coordB){
    /* Check that x and y coordinates are equal*/
    if (coordA->x == coordB->x && coordA->y == coordB->y)
        return 1;
    return 0;
}
