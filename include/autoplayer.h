#pragma once

// Required Files
#include "Board.h"

/**
 * Find hole in partial complete row/col and mark it
 */
void markPartialRow(Board *board, int row, int isVertical);

int isRowPartialComplete(Board *board, int row, int isVertical, char lastMark);

/**
 * Find partial complete row/col and mark it
 */
int getPartialCompleteRow(Board *board, int isVertical, char lastMark);

/**
 * Find hole in partial complete diagonal and mark it
 */
void markPartialDiagonal(Board *board, int isPrinciple);

/**
 * Find partial complete diagonal and mark it
 */
int markPartialCompleteDiagnal(Board *board, int isPrinciple, char mark);

/**
 * Checks if the oponent already marked on opposite corner
 */
int isOppositeCorner(Board *board, int x, int y);

/**
 * marks the given cell and toggle player turn
 */
void markCell(Board *board, Cell *cell, char mark);

/**
 * Find and mark opposite empty corner (where opponent already marked)
 */
int markOppositeEmptyCorner(Board *board);

/**
 * Find and marks the empty corner
 */
int markEmptyCorner(Board *board);

int hasRowFork(Board *board, int num, int isVert);

/**
 * Find and marks on any of the empty side
 */
int markEmptySide(Board *board, int forksOnly);

int isForkCell(Board *board, int x, int y, char player);

int markForkCell(Board *board, char player);

/**
 * Tries to calculate the best move and mark it on the board
 */
void markBestMove(Board *board, int height, int width);
