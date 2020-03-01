#pragma once

#include "Board.h"

typedef struct
{
    Board board;
    int height;
    int width;
    int comPlayer;
} Game;

/**
 * Game Constructor
 */
Game Game_init();

/**
 *  Checks for mark won 
 */
char Game_isWon(Game *game);

/**
 *  Checks for Game Draw 
 */
int Game_isDrawn(Game *game);

/**
 * keep updating throughout the game
 */
void Game_startMainLoop(Game *game);
