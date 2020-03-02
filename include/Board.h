#pragma once

#include <stdlib.h>

#include "Cell.h"

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

/**
 * Mark the cell at pos
 */
int Board_markAt(Board *board, int pos);