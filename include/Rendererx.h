#pragma once

#ifdef XTERM
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

#define DRAW_L1 "\e[34m ██████╗ ██████╗  █████╗ ██╗    ██╗ \e[0m"
#define DRAW_L2 "\e[34m ██╔══██╗██╔══██╗██╔══██╗██║    ██║ \e[0m"
#define DRAW_L3 "\e[34m ██║  ██║██████╔╝███████║██║ █╗ ██║ \e[0m"
#define DRAW_L4 "\e[34m ██║  ██║██╔══██╗██╔══██║██║███╗██║ \e[0m"
#define DRAW_L5 "\e[34m ██████╔╝██║  ██║██║  ██║╚███╔███╔╝ \e[0m"
#define DRAW_L6 "\e[34m ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝  \e[0m"

#define WONL1 "\e[34m██╗    ██╗ ██████╗ ███╗   ██╗\e[0m"
#define WONL2 "\e[34m██║    ██║██╔═══██╗████╗  ██║\e[0m"
#define WONL3 "\e[34m██║ █╗ ██║██║   ██║██╔██╗ ██║\e[0m"
#define WONL4 "\e[34m██║███╗██║██║   ██║██║╚██╗██║\e[0m"
#define WONL5 "\e[34m╚███╔███╔╝╚██████╔╝██║ ╚████║\e[0m"
#define WONL6 "\e[34m ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝\e[0m"

#define XL1 "\e[31m ██╗  ██╗\e[0m"
#define XL2 "\e[31m ╚██╗██╔╝\e[0m"
#define XL3 "\e[31m  ╚███╔╝ \e[0m"
#define XL4 "\e[31m  ██╔██╗ \e[0m"
#define XL5 "\e[31m ██╔╝ ██╗\e[0m"
#define XL6 "\e[31m ╚═╝  ╚═╝\e[0m"

#define OL1 "\e[33m ██████╗ \e[0m"
#define OL2 "\e[33m██╔═══██╗\e[0m"
#define OL3 "\e[33m██║   ██║\e[0m"
#define OL4 "\e[33m██║   ██║\e[0m"
#define OL5 "\e[33m╚██████╔╝\e[0m"
#define OL6 "\e[33m ╚═════╝ \e[0m"

#define TTT1 "\e[31m██████████╗ \e[33m██████████╗     \e[34m██████████╗   ██████╗\e[0m"
#define TTT2 "\e[31m╚═══██╔═══╝ \e[33m╚═══██╔═══╝     \e[34m╚═══██╔═══╝   ██╔═══╝\e[0m"
#define TTT3 "\e[31m    ██║██╗ ████╗\e[33m██║██████╗ ████╗\e[34m██║██████╗██████╗\e[0m"
#define TTT4 "\e[31m    ██║██║██╔══╝\e[33m██║██║ ██║██╔══╝\e[34m██║██║ ██║██╔═══╝\e[0m"
#define TTT5 "\e[31m    ██║██║╚████╗\e[33m██║███████╗████╗\e[34m██║██████║██████╗\e[0m"
#define TTT6 "\e[31m    ╚═╝╚═╝ ╚═══╝\e[33m╚═╝╚══════╝╚═══╝\e[34m╚═╝╚═════╝╚═════╝\e[0m"

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

void Game_loop(Game *game);

void sizeFix(Game *game);

#endif
