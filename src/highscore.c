/*bitmaps.c
    Created by Tenzin Sangpo Choedon
*/
#include "functions.h"

Highscore highscore_list[3];

/* Compute the highscore */
void compute_highscore()
{
    int i;

    // Score starts with the players score
    int score = player.coins;
    int temp;

    /* Check each highscore*/
    for (i = 0; i < 3; i++)
    {
        /* Check each score against a highscore*/
        if (score > highscore_list[i].score)
        {

            // Swap places
            temp = highscore_list[i].score;
            highscore_list[i].score = score;
            score = temp;
        }
    }
}
