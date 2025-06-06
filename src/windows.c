/* windows.c
    Created by Tenzin Sangpo Choedon
*/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

int countTickFoodEffect;

/*MENU BUTTONS: BTN4 - first option, BTN3 - second option */

void window_menu()
{
    display_text(0, "MENU", 0);
    display_text(1, "BTN4: START GAME", 0);
    display_text(2, "BTN3: HIGHSCORE", 0);

    int buttonInfo = get_buttons();

    // Start playing if BTN4 is pressed
    if (buttonInfo == BTN4)
    {
        quicksleep(1000000);
        // Change playing_state to start playing
        playing_state = START_PLAYING;

        // Change main_state to playing
        main_state = PLAYING;
    }

    // Display highscores if BTN3 is pressed
    if (buttonInfo == BTN3)
    {
        quicksleep(1000000);
        // Change main_state to highscore
        main_state = HIGHSCORES;
    }
}

void window_game()
{

    // When starting to play load the game
    if (playing_state == START_PLAYING)
    {
        load_game();
        // Continue to play
        playing_state = CONTINUE_PLAYING;
    }

    // Food effect is activated
    if (playing_state == FOOD_EFFECT)
    {
        countTickFoodEffect++;
    }

    // Food effect is deactivated within 10 seconds
    if (countTickFoodEffect == 100)
    {
        playing_state = CONTINUE_PLAYING;
        countTickFoodEffect = 0;
    }

    // Update the ghosts, player, playfield
    update_game();

    // Check the state of the player
    if (player.player_state != 0)
    {
        // Draw the updated playfield, ghost, player
        draw_game();
    }

    // Update state for main, player, ghosts
    update_state();
}

void window_highscore()
{
    // Convert lives to string
    char highscore1[22];
    itocharconv(highscore_list[0].score, &highscore1[22]);

    // Convert lives to string
    char highscore2[22];
    itocharconv(highscore_list[1].score, &highscore2[22]);

    // Convert lives to string
    char highscore3[22];
    itocharconv(highscore_list[2].score, &highscore3[22]);

    // Display the text
    display_text(0, &highscore1[22], 10);
    display_text(1, &highscore2[22], 10);
    display_text(2, &highscore3[22], 10);
    display_text(3, "BTN4: MENU", 10);

    int buttonInfo = get_buttons();

    // Return to menu if BTN4 is pressed
    if (buttonInfo == BTN4)
    {
        quicksleep(1000000);
        // Change main_state to menu
        main_state = MENU;
    }
}

void window_dead()
{

    // Convert lives to string
    char buffer[22];
    itocharconv(player.lives, &buffer[22]);

    // Display the text
    display_text(0, "YOU ARE DEAD", 10);
    display_text(1, "Lives left: ", 10);
    display_text(2, &buffer[22], 10);
    display_text(3, "BTN4: CONTINUE", 10);

    int buttonInfo = get_buttons();

    // Continue playing if BTN4 is pressed
    if (buttonInfo == BTN4)
    {
        quicksleep(1000000);
        // Change main_state to playing
        main_state = PLAYING;

        // Respawn player
        respawn_player();
    }
}

void window_gameover()
{

    // Convert lives to string
    char buffer[22];
    itocharconv(player.coins, &buffer[22]);

    // Display the text
    display_text(0, "GAMEOVER", 10);
    display_text(1, "SCORE: ", 10);
    display_text(2, &buffer[22], 10);
    display_text(3, "BTN4: MENU", 10);
    int buttonInfo = get_buttons();

    // Return to menu if BTN4 is pressed
    if (buttonInfo == BTN4)
    {
        quicksleep(1000000);
        // Change main_state to menu
        main_state = MENU;
    }
}

void window_won()
{

    // Convert lives to string
    char buffer[22];
    itocharconv(player.coins, &buffer[22]);

    // Display the text
    display_text(0, "WON", 10);
    display_text(1, "SCORE: ", 10);
    display_text(2, &buffer[22], 10);
    display_text(3, "BTN4: MENU", 10);

    int buttonInfo = get_buttons();

    // Return to menu if BTN4 is pressed
    if (buttonInfo == BTN4)
    {
        quicksleep(1000000);
        // Change main_state to menu
        main_state = MENU;
    }
}