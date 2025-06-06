/*game.c
    Created by Tenzin Sangpo Choedon
*/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

Player player;
Ghost ghosts[NUMBER_OF_GHOST];

/* Draw game every window tick*/
void draw_game(){
    int i;

    // Draw updated playfield
    draw_playfield();

    /* Draw updated player if state of the player is alive */
    if(player.player_state == 1){
        draw_player();
    }
    

    /* Draw updated ghosts if state of the ghost is alive*/
	for(i = 0; i< NUMBER_OF_GHOST; ++i){
        if(ghosts[i].ghost_state == 1){
            draw_ghost(&ghosts[i]);
        }
	}
}

/* Update the game every window tick*/
void update_game(){
    int i;
    
    // Moves player
    move_player();

    // Moves all ghosts
    for(i = 0; i<NUMBER_OF_GHOST; ++i){

        // Move one ghost
		move_ghost(&ghosts[i]);

        /* Pass through the portal if ghost is on the portal*/
        if(get_pixelData(&ghosts[i].position) == PORTAL){
            pass_through_portal(&ghosts[i].position);
        }
	}

    /* Pass through the portal if player is on the portal*/
    if(get_pixelData(&player.position) == PORTAL){
        pass_through_portal(&player.position);
    }
    
    /* Consume food if the player is on a food*/
    else if((get_pixelData(&player.position) & FOOD) == FOOD){
        consume_food();
    }

    /* Take coins in the 5x5 space that player has*/
    take_coins();
}

void update_state(){
    int j;

    /* Check if there is a collision between player and any ghosts*/
    for(j = 0; j<NUMBER_OF_GHOST; ++j){

        // Collision with an alive ghost
        if(collision(&player, &ghosts[j]) && ghosts[j].ghost_state == 1){

            // Food effect is activated then the ghost is dead
            if(playing_state == FOOD_EFFECT){
                
                // the ghost is dead
                ghosts[j].ghost_state = 0;

                // decrement number of ghosts
                playfield.numberOfGhostsLeft--;
            }
            // No food effect then the player is dead
            else{
                
                // the player is dead
                player.player_state = 0;
            }
        }
    }

    // Check the state of the player
    if(player.player_state == 0){

        // Decrement the players lives
           player.lives --;

        // Player has lives left
        if(player.lives > 0 ){

            // The player is alive
            player.player_state = 1;

            // Change playing_state to dead
            main_state = DEAD;
        }

        // Player has no lives left
        else{
            compute_highscore();
            // Change main_state to GAMEOVER
            main_state = GAMEOVER;
        }
    }

    // No ghosts left
    if(playfield.numberOfGhostsLeft == 0){
        compute_highscore();
        // Change main_state to WON
        main_state = WON;
    }
}

// Denna ska kallas först så fort vi börjar PLAYING
void load_game(){
    int i;
    
    // Initialize playfield includes position for food, spawning for ghost and player, portals
    init_playfield();

    // Initialize player
    init_player();

    /* Initialize all ghosts*/
	for(i = 0; i<NUMBER_OF_GHOST; ++i){
		init_ghost(&ghosts[i], playfield.spawn[i]);
	}

    // Load 2D map
    load_map();

    // Load coins into map
    load_coins();
}
