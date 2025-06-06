
/* playfield.c 
	Created by Tenzin Sangpo Choedon
*/
#include <stdlib.h>
#include <stdint.h>
#include "functions.h"

int8_t map[MP_COLUMNS][MP_ROWS];

Playfield playfield;

/*Load playfield*/
void init_playfield(){
	playfield.map=map_1;
	playfield.numberOfGhostsLeft = NUMBER_OF_GHOST;
	playfield.origin = (Coord) {63, 28};
	playfield.spawn[0] = (Coord) {58, 3};
	playfield.spawn[1] = (Coord) {63, 3};
	playfield.spawn[2] = (Coord) {68, 3};
	playfield.food[0] = (Coord) {3, 3};
	playfield.food[1] = (Coord) {3, 28};
	playfield.food[2] = (Coord) {124, 3};
	playfield.food[3] = (Coord) {124, 28};
	playfield.portal[0].in = (Coord) {0, 15};
	playfield.portal[0].out =(Coord) {127, 15};
	playfield.portal[1].in = (Coord) {127, 15};
	playfield.portal[1].out =(Coord) {0, 15};
}

/*Draw playfield*/
void draw_playfield(){
	draw_map();
	draw_food();
}

/*Load map data into map*/
void load_map(void){
	int currentColumn, currentRow;

	for(currentColumn = 0; currentColumn < MP_COLUMNS; ++currentColumn)
	{
		for(currentRow = 0; currentRow < MP_ROWS; ++currentRow)
		{
			map[currentColumn][currentRow] = playfield.map[currentRow*MP_COLUMNS + currentColumn];
		}
	}
}

/*Load coins into the map*/
void load_coins(void){
	int currentColumn, currentRow, i, j;

	for(currentRow = 0; currentRow < MP_ROWS; ++currentRow)
	{
		for(currentColumn = 0; currentColumn < MP_COLUMNS; ++currentColumn)
		{
			if(map[currentColumn][currentRow] == EMPTY ){

				/*Check if the space around contains any COINS, FOOD or Portals*/
				for(i = -2; i <= 2; ++i){
					for(j = -2; j <= 2; ++j){
						if(get_pixelData(&(Coord){currentColumn + i, currentRow + j}) & ( COIN| FOOD | PORTAL)){
							goto next;
						}
					}
				}
				map[currentColumn][currentRow] = COIN;
			}
			next: ;
		}
    }
}

/* Draw map and coins*/
void draw_map(void){
	int currentColumn, currentRow;

	for(currentRow = 0; currentRow < MP_ROWS; ++currentRow)
	{
		for(currentColumn = 0; currentColumn < MP_COLUMNS; ++currentColumn)
		{
			display_set(currentColumn, currentRow, map[currentColumn][currentRow] & (WALL|COIN));
		}
	}
}

/* Draw food */
void draw_food(){
	int i, y, x;
	for(i = 0; i < NUMBER_OF_FOOD; ++i){
		for(y = 0; y < SIZE_OF_FOOD; ++y)
		{
			for(x = 0; x < SIZE_OF_FOOD; ++x)
			{
				/* If there is a food then display it*/
				if((get_pixelData(&playfield.food[i]) & FOOD) == FOOD){
					display_set(x - 1 + playfield.food[i].x, y -1 + playfield.food[i].y, food[y*SIZE_OF_FOOD + x]);
				}
			}
		}
	}
}

/* Pass through the portal*/
void pass_through_portal(Coord *coord){
	int j;
	for(j = 0; j < NUMBER_OF_PORTALS; ++j) {
		
		if(equal_coordinate(coord, &playfield.portal[j].in)){
			copy_coordinate(coord, playfield.portal[j].out);
			break;
		}
	}
}

/* Take coins*/
void take_coins(){
	int i,j;

	/*Check if the space around player contains any COINS*/
	for(i = -2; i <= 2; ++i){
		for(j = -2; j <= 2; ++j){

			/* Check that there is a COIN*/
			if(get_pixelData(&(Coord){player.position.x + i, player.position.y + j}) & (COIN)){
				player.coins++;
				map[player.position.x + i][player.position.y + j] = EMPTY;
			}
		}
	}
}

/* Consume food*/
void consume_food(){
	// Change playing state
	playing_state = FOOD_EFFECT;
	// Empty the pixel on the map
	map[player.position.x][player.position.y] = EMPTY;
	// New food is consumed so reset counter
	countTickFoodEffect = 0;
}

/* Respawn player */
void respawn_player(){
	copy_coordinate(&player.position, playfield.origin);
	player.graphic = player_basic;
}

/* Get the data at the coordinate*/
int get_pixelData(Coord const *coord){
	if(!valid_coordinate(coord)){
		return EMPTY;
	}
	else{
		return map[coord->x][coord->y];
	}
}

/* Confirm if there is a collision between ghost and player*/
int collision(Player *player, Ghost *ghost){
	if((abs(player->position.x - ghost->position.x) < 5) && (abs(player->position.y - ghost->position.y) < 5)){
		return 1;
	}
	else {
		return 0;
	}
}

