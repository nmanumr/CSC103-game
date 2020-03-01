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
 * Checks and return Current Game State
 * @return
 * 0 for Game Continued 
 * 1 for X WON
 * 2 for O WON
 * 3 for Game Draw
 */
int GameState(Game *game);

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
