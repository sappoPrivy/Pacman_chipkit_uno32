/*player.c
	Created by Tenzin Sangpo Choedon
*/
#include <stdint.h>   
#include <pic32mx.h>  
#include "functions.h"  


/* Initialize player at origin*/
void init_player(){
	player.graphic=player_basic;

    // Spawn player at origin
	copy_coordinate(&player.position, playfield.origin);
    
    // Initial lives are 3
	player.lives=3;
    
    // Initialize amount of coins
    player.coins = 0;

    // Player is alive
    player.player_state = 1;
}

/* Draw player at a position */
void draw_player(){
	int y, x;

	for(y = 0; y < SIZE_OF_PLAYER; ++y)
	{
		for(x = 0; x < SIZE_OF_PLAYER; ++x)
		{
			display_set(x - 2 + player.position.x, y -2 + player.position.y, player.graphic[y*SIZE_OF_PLAYER + x]);
		}
	}
}

/* Check new position is valid*/
int valid_player_position(int x, int y){

    // Check if the new position is inacessable
    if(get_pixelData(&(Coord){player.position.x + x, player.position.y + y}) & (INACCESSIBLE | GHOST))
        return 0;

    // Otherwise the position is valid
    return 1;
}

/* Move the player according to which button is pressed*/
void move_player(){
    // * in game BTN1 - Right, BTN2 - Down, BTN3 - Up, BTN4 - Left
    int buttonsData = get_buttons();

    /* Move right if BTN1 is pressed*/
    if(buttonsData== BTN1 && valid_player_position(1, 0)){
        mod_coordinate(&player.position, 1, 0);   // Change position
        player.graphic=player_right;         // Change graphical icon
    }
    /* Move down if BTN2 is pressed*/
    if (buttonsData == BTN2 && valid_player_position(0, 1)){
        mod_coordinate(&player.position, 0, 1);   // Change position
        player.graphic=player_down;        // Change graphical icon
    }
    /* Move up if BTN3 is pressed*/
    if(buttonsData == BTN3 && valid_player_position(0, -1)){
        mod_coordinate(&player.position, 0, -1);  // Change position
        player.graphic=player_up;        // Change graphical icon
    }
    /* Move left if BTN4 is pressed */
    if(buttonsData == BTN4 && valid_player_position(-1, 0)) {
        mod_coordinate(&player.position, -1, 0);  // Change position
        player.graphic=player_left;         // Change graphical icon
    }
    /* No button pressed*/
    if(buttonsData == 0){
        player.graphic=player_basic;    // Change graphical icon
    }
}

