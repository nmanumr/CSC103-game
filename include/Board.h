#pragma once

#include <stdlib.h>

#include "Cell.h"

#define RED_FG "\e[31m"
#define YLOW_FG "\e[33m"

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

typedef struct
{
    int size;
    Cell *cells;
    char turn;
    int selected;
} Board;

/**
 * Board Constructor
 */
Board Board_init(int size);

/**
 * Returns a cell from given XY position
 */
Cell Board_getCellFromXY(Board board, int x, int y);

Cell *Board_getCellAddrsFromXY(Board board, int x, int y);

/**
 *  Removes the hover mark
 */
void Board_deselect(Board *board);

/**
 *  mark cell hovered 
 */
void Board_select(Board *board);

/**
 * Moves the current selection
 */
void Board_move(Board *board, char dir);

/**
 * Toggle player turn
 */
void Board_toggleTurn(Board *board);

/**
 * Mark the current selected cell
 */
void Board_mark(Board *board);
