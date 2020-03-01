// Required Files
#include "Board.h"
#include "autoplayer.h"

int i, j;

/**
 * Find hole in partial complete row/col and mark it
 */
void markPartialRow(Board *board, int row, int isVertical)
{
    for (j = 0; j < board->size; j++)
    {
        Cell *cell = Board_getCellAddrsFromXY(*board, isVertical ? j : row, isVertical ? row : j);

        if (cell->isEmpty)
        {
            Cell_mark(cell, board->turn);
            Board_toggleTurn(board);
        }
    }
}

int isRowPartialComplete(Board *board, int row, int isVertical, char lastMark)
{
    int empty = 0;

    for (j = 0; j < board->size; j++)
    {
        Cell cell = Board_getCellFromXY(*board, isVertical ? j : row, isVertical ? row : j);
        if (cell.isEmpty)
            ++empty;

        else if (lastMark == ' ' && cell.mark != ' ')
            lastMark = cell.mark;

        else if (cell.mark != ' ' && cell.mark != lastMark)
        {
            empty = 0;
            break;
        }
    }

    return empty;
}

/**
 * Find partial complete row/col and mark it
 */
int getPartialCompleteRow(Board *board, int isVertical, char lastMark)
{
    for (i = 0; i < board->size; i++)
        if (isRowPartialComplete(board, i, isVertical, lastMark) == 1)
        {
            markPartialRow(board, i, isVertical);
            return 1;
        }

    return 0;
}

/**
 * Find hole in partial complete diagonal and mark it
 */
void markPartialDiagonal(Board *board, int isPrinciple)
{
    for (i = 0; i < board->size; i++)
    {
        Cell *cell = Board_getCellAddrsFromXY(*board, isPrinciple ? i : board->size - i - 1, i);

        if (cell->isEmpty)
        {
            Cell_mark(cell, board->turn);
            Board_toggleTurn(board);
        }
    }
}

/**
 * Find partial complete diagonal and mark it
 */
int markPartialCompleteDiagnal(Board *board, int isPrinciple, char mark)
{
    int empty = 0;
    for (i = 0; i < board->size; i++)
    {
        Cell cell = Board_getCellFromXY(*board, isPrinciple ? i : board->size - i - 1, i);

        if (cell.isEmpty)
            ++empty;

        else if (mark == ' ' && cell.mark != ' ')
            mark = cell.mark;

        else if (cell.mark != ' ' && cell.mark != mark)
        {
            empty = 0;
            break;
        }

        if (empty > 1)
            break;
    }
    if (empty == 1)
    {
        markPartialDiagonal(board, isPrinciple);
        return 1;
    }
    return 0;
}

/**
 * Checks if the oponent already marked on opposite corner
 */
int isOppositeCorner(Board *board, int x, int y)
{
    char turn = board->turn == 'X' ? 'O' : 'X';
    return Board_getCellFromXY(*board, x, y).mark == turn;
}

/**
 * marks the given cell and toggle player turn
 */
void markCell(Board *board, Cell *cell, char mark)
{
    Cell_mark(cell, mark);
    Board_toggleTurn(board);
}

/**
 * Find and mark opposite empty corner (where opponent already marked)
 */
int markOppositeEmptyCorner(Board *board)
{
    if (Board_getCellFromXY(*board, 0, 0).isEmpty && isOppositeCorner(board, board->size - 1, board->size - 1))
        markCell(board, Board_getCellAddrsFromXY(*board, 0, 0), board->turn);

    else if (Board_getCellFromXY(*board, board->size - 1, 0).isEmpty && isOppositeCorner(board, 0, board->size - 1))
        markCell(board, Board_getCellAddrsFromXY(*board, board->size - 1, 0), board->turn);

    else if (Board_getCellFromXY(*board, 0, board->size - 1).isEmpty && isOppositeCorner(board, board->size - 1, 0))
        markCell(board, Board_getCellAddrsFromXY(*board, 0, board->size - 1), board->turn);

    else if (Board_getCellFromXY(*board, board->size - 1, board->size - 1).isEmpty && isOppositeCorner(board, 0, 0))
        markCell(board, Board_getCellAddrsFromXY(*board, board->size - 1, board->size - 1), board->turn);

    else
        return 0;
    return 1;
}

/**
 * Find and marks the empty corner
 */
int markEmptyCorner(Board *board)
{
    if (Board_getCellFromXY(*board, 0, 0).isEmpty)
        markCell(board, Board_getCellAddrsFromXY(*board, 0, 0), board->turn);

    else if (Board_getCellFromXY(*board, board->size - 1, 0).isEmpty)
        markCell(board, Board_getCellAddrsFromXY(*board, board->size - 1, 0), board->turn);

    else if (Board_getCellFromXY(*board, 0, board->size - 1).isEmpty)
        markCell(board, Board_getCellAddrsFromXY(*board, 0, board->size - 1), board->turn);

    else if (Board_getCellFromXY(*board, board->size - 1, board->size - 1).isEmpty)
        markCell(board, Board_getCellAddrsFromXY(*board, board->size - 1, board->size - 1), board->turn);

    else
        return 0;
    return 1;
}

int hasRowFork(Board *board, int num, int isVert)
{
    for (j = 0; j < board->size; j++)
    {
        Cell cell = Board_getCellFromXY(*board, isVert ? j : num, isVert ? num : j);
        if (cell.mark != 'O' && !cell.isEmpty)
            return 0;
    }
    return 1;
}

/**
 * Find and marks on any of the empty side
 */
int markEmptySide(Board *board, int forksOnly)
{
    for (i = 1; i < board->size - 1; i++)
    {
        if (hasRowFork(board, i, 0) && Board_getCellFromXY(*board, i, 0).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, i, 0), board->turn);

        else if (hasRowFork(board, i, 1) && Board_getCellFromXY(*board, 0, i).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, 0, i), board->turn);

        else if (hasRowFork(board, i, 1) && Board_getCellFromXY(*board, board->size - 1, i).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, board->size - 1, i), board->turn);

        else if (hasRowFork(board, i, 0) && Board_getCellFromXY(*board, i, board->size - 1).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, i, board->size - 1), board->turn);

        // top side
        else if (!forksOnly && Board_getCellFromXY(*board, i, 0).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, i, 0), board->turn);

        // left side
        else if (!forksOnly && Board_getCellFromXY(*board, 0, i).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, 0, i), board->turn);

        // right side
        else if (!forksOnly && Board_getCellFromXY(*board, board->size - 1, i).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, board->size - 1, i), board->turn);

        // bottom side
        else if (!forksOnly && Board_getCellFromXY(*board, i, board->size - 1).isEmpty)
            markCell(board, Board_getCellAddrsFromXY(*board, i, board->size - 1), board->turn);

        else
            continue;
        return 1;
    }
    return 0;
}

int isForkCell(Board *board, int x, int y, char player)
{
    if (isRowPartialComplete(board, y, 1, player) == 2 &&
        isRowPartialComplete(board, x, 0, player) == 2 &&
        Board_getCellFromXY(*board, x, y).isEmpty)
        return 1;
    return 0;
}

int markForkCell(Board *board, char player)
{
    int i, j;
    for (i = 0; i < board->size; i++)
    {
        for (j = 0; j < board->size; j++)
        {
            if (isForkCell(board, j, i, player))
            {
                markCell(board, Board_getCellAddrsFromXY(*board, j, i), board->turn);
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Tries to calculate the best move and mark it on the board
 */
void markBestMove(Board *board, int height, int width)
{
    Cell centerCell = board->cells[(board->size * board->size - 1) / 2];

    // Win or block winning rows/cols
    if (getPartialCompleteRow(board, 0, 'O'))
        return;
    else if (getPartialCompleteRow(board, 1, 'O'))
        return;

    else if (getPartialCompleteRow(board, 0, 'X'))
        return;
    else if (getPartialCompleteRow(board, 1, 'X'))
        return;

    // Win or block winning digonals
    else if (markPartialCompleteDiagnal(board, 1, 'O'))
        return;
    else if (markPartialCompleteDiagnal(board, 0, 'O'))
        return;

    else if (markPartialCompleteDiagnal(board, 1, 'X'))
        return;
    else if (markPartialCompleteDiagnal(board, 0, 'X'))
        return;

    // take center
    else if (centerCell.isEmpty)
    {
        Cell_mark(&board->cells[(board->size * board->size - 1) / 2], board->turn);
        Board_toggleTurn(board);
    }

    else if (centerCell.mark == 'O' && markEmptySide(board, 1))
        return;

    // take opposite corner
    else if (markOppositeEmptyCorner(board))
        return;

    // take empty corner
    else if (markEmptyCorner(board))
        return;

    // fork
    else if (markForkCell(board, 'O'))
        return;
    // block fork
    else if (markForkCell(board, 'X'))
        return;

    // take empty side
    else
        markEmptySide(board, 0);
}