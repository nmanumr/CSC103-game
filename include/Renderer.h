#pragma once

#include "Game.h"

// Colors defined
#define INVERT "\e[7m"
#define RESET "\e[0m"
#define BLINK "\e[5m"
#define DEBLINK "\e[25m"
#define RED_FG "\e[31m"
#define RED_BG "\e[41m"
#define YLOW_FG "\e[33m"
#define YLOW_BG "\e[43m"

// console functions
#define gotoxy(y, x) fprintf(stdout, "\033[%d;%dH", (y), (x))
#define clear() fprintf(stdout, "\033[2J")

/**
 *  Renders the header  
 */
void Game_renderHeader(Game *game);

/**
 *  Renders the Table/board on console 
 */
void Game_renderBoard(Game *game);

/**
 *  Renders Footer/KeyNotes 
 */
void Game_renderKeyMap(Game *game);

/**
 *  Renders the Enteries on table/board 
 */
void Game_renderInputDialog(Game *game, char str[], int *var_addr);

void Game_renderSplash(Game *game);

/**
 *  Renders Mark won Splash 
 */
void Game_renderWon(Game *game, char player);

/**
 *  renders Drawn Splash 
 */
void Game_renderDrawn(Game *game);

void Game_renderTurn(Game *game);

/**
 *  clears size input dialog
 */
void Game_clearDialog(Game *game);

/**
 *  Renders the complete game 
 */
void Game_render(Game *game);

/**
 * Checks and return Current Game State
 * @return
 * 0 for Game Continued 
 * 1 for X WON
 * 2 for O WON
 * 3 for Game Draw
 */
int GameState(Game *game);

void sizeFix(Game *game);
