/* functions.h
	Created by Tenzin Sangpo Choedon
*/
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*Macros for display on microcontroller*/
/*BEGINNING OF COPIED CODE*/
#define COMMAND_MODE (PORTFCLR = 0x10)
#define DATA_MODE (PORTFSET = 0x10)

#define ACTIVATE_RESET (PORTGCLR = 0x200)
#define DO_NOT_RESET (PORTGSET = 0x200)

#define ACTIVATE_VDD (PORTFCLR = 0x40)
#define ACTIVATE_VBAT (PORTFCLR = 0x20)

#define TURN_OFF_VDD (PORTFSET = 0x40)
#define TURN_OFF_VBAT (PORTFSET = 0x20)
/*END OF COPIED CODE*/

/*Macros for dimension of the display*/
#define DISPLAY_COLUMNS 128
#define DISPLAY_ROWS 32
#define DISPLAY_PAGES 4

/*Macros for maps*/
#define E EMPTY
#define W WALL
#define I INACCESSIBLE
#define G GHOST
#define P PORTAL
#define F FOOD
#define S G // Spawn a ghost
#define O E // Origin is empty space

/*Macros for dimension of the map*/
#define MP_COLUMNS 128
#define MP_ROWS 32

/* Macros for icons */
#define NUMBER_OF_GHOST 3
#define NUMBER_OF_FOOD 4
#define NUMBER_OF_PORTALS 2
#define SIZE_OF_FOOD 3
#define SIZE_OF_PLAYER 5
#define SIZE_OF_GHOST 5

/* Macros for buttons */
#define BTN1 1
#define BTN2 2
#define BTN3 4
#define BTN4 8

/*Macros for different menu, game, ghost, player states*/
#define PLAYING 10
#define CONTINUE_PLAYING 12
#define START_PLAYING 13
#define MENU 14
#define HIGHSCORES 15
#define DEAD 16
#define ALIVE 17
#define GAMEOVER 18
#define FOOD_EFFECT 19
#define WON 20

/*Enum values for data in a pixel on a map*/
enum PIXELDATA
{
	EMPTY = 0x00,
	WALL = 0x01,
	INACCESSIBLE = 0x02,
	GHOST = 0x04,
	COIN = 0x08,
	FOOD = 0x10,
	PORTAL = 0x20,
};

/*Struct for coordinates*/
typedef struct COORD
{
	int8_t x;
	int8_t y;
} Coord;

/*Struct for a portal*/
typedef struct PORTAL
{
	Coord in;
	Coord out;
} Portal;

/*Struct for a playfield*/
typedef struct PLAYFIELD
{
	Coord origin;					  // Spawn player
	Coord spawn[NUMBER_OF_GHOST];	  // Spawn ghost
	Coord food[NUMBER_OF_FOOD];		  // Food
	Portal portal[NUMBER_OF_PORTALS]; // Portal
	int8_t const *map;				  // This points toward our map
	int numberOfGhostsLeft;			  // Amount of ghosts left
} Playfield;

/*Struct for Player*/
typedef struct PLAYER
{
	int8_t const *graphic; // Pointer to the graphics of a player
	Coord position;		   // Position
	int lives;			   // Lives
	int coins;			   // Amount of coins
	int player_state;	   // The state of the player
} Player;

/*Struct for Ghost*/
typedef struct Ghost
{
	int8_t const *graphic; // Pointer to the graphics of a Ghost
	Coord position;		   // Position
	int ghost_state;	   // ghost state
	int randomDirection;   // direction for ghost
	int randomSteps;	   // number of steps for ghost
} Ghost;

typedef struct Highscore
{
	// char player_name[3];
	int score;
} Highscore;

/*Bitmaps for a different icons*/
extern int8_t const player_up[];
extern int8_t const player_left[];
extern int8_t const player_down[];
extern int8_t const player_right[];
extern int8_t const player_basic[];
extern int8_t const food[];
extern int8_t const ghost_basic[];
extern const int8_t const font[128 * 8];

/* Extern variables*/
extern Playfield playfield;
extern Player player;
extern Ghost ghosts[NUMBER_OF_GHOST];
extern int main_state;
extern int playing_state;
extern int8_t const map_1[MP_COLUMNS * MP_ROWS];
extern int countTickFoodEffect;
extern Highscore highscore_list[3];

/*Functions for display*/
void display_init(void);
void display_set(int, int, int);
void display_update(void);
void display_text(int, char const *, int);
void display_clear(void);
void itocharconv(int, char *);
void quicksleep(int);

/*Functions for playfield*/
void init_playfield(void);
void draw_playfield(void);
void take_coins(void);
void pass_through_portal(Coord *);
void consume_food(void);
int collision(Player *, Ghost *);
void respawn_player(void);

/*Functions for map*/
void load_map(void);
void draw_map(void);
void load_coins(void);
void draw_food(void);
int get_pixelData(Coord const *);

/*Functions for player*/
void init_player(void);
void draw_player(void);
int valid_player_position(int, int);
void move_player(void);

/*Functions for ghost*/
void init_ghost(Ghost *, Coord);
void draw_ghost(Ghost *);
int valid_ghost_position(Ghost *, int, int);
void move_ghost(Ghost *);

/*Functions for game*/
void load_game(void);
void draw_game(void);
void update_game(void);
void update_state(void);

/*Functions for showing a window for different states*/
void window_menu(void);
void window_game(void);
void window_highscore(void);
void window_dead(void);
void window_gameover(void);
void window_won(void);

/*Functions for peripherlas*/
void buttons_init(void);
int8_t get_buttons(void);
void timer_init(void);
void spi_init(void);
void peripherals_init(void);
void interrupt_init(void);

/*Functions for coordinates*/
void copy_coordinate(Coord *, Coord);
void mod_coordinate(Coord *, int, int);
int valid_coordinate(Coord const *);
int equal_coordinate(Coord const *, Coord const *);

/*Functions for Highscore*/
void compute_highscore(void);