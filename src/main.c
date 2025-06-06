/* main.c

   Created by Tenzin Sangpo Choedon
*/

#include <stdint.h>
#include <pic32mx.h>
#include "functions.h"

void *stdin, *stdout, *stderr;

int main_state = MENU;
int playing_state;

void init()
{
	peripherals_init();
	spi_init();
	display_init();
	buttons_init();
	timer_init();
	interrupt_init();
}

/*Interrupt routine to update the window each 10 ms*/
void window_tick()
{

	switch (main_state)
	{
	case MENU:
		// call upon menu options
		window_menu();
		break;

	case PLAYING:
		// call upon the game window
		window_game();
		break;

	case HIGHSCORES:
		// call upon display highscores
		window_highscore();
		break;

	case DEAD:
		// call upon dead window
		window_dead();
		break;

	case GAMEOVER:
		// call upon gameover window
		window_gameover();
		break;

	case WON:
		// call upon won window
		window_won();
		break;
	}

	// Update and clear display
	display_update();
	display_clear();

	// Reset interrupt flag
	IFS(0) = IFS(0) & 0xFFFFFEFF;
}

int main(void)
{
	init();
	return 0;
}
