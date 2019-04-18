#include "Cell.h"
#include <stdlib.h>

int i;

struct Board
{
    int size;
    struct Cell *cells;
    char turn;
    int selected;
};

/**
 * Board Constructor
 */
struct Board Board_init(int size)
{
    struct Cell *cells = malloc(sizeof(Cell_init()) * size * size);

    // intialize cells array mein empty Cell as variable
    // array intialization is not supported
    for (i = 0; i < size * size; i++)
    {
        cells[i] = Cell_init();
    }

    struct Board board = {.size = size, .cells = cells, .selected = 0, .turn = 'X'};
    return board;
}

/**
 * Returns a cell from given XY position
 */
struct Cell Board_getCellFromXY(struct Board board, int x, int y)
{
    return board.cells[board.size * y + x];
}

void Board_deselect(struct Board *board)
{
    board->cells[board->selected].isHoved = 0;
}

void Board_select(struct Board *board)
{
    if (board->selected >= board->size * board->size)
    {
        board->selected = board->size * board->size - 1;
    }
    else if (board->selected < 0)
    {
        board->selected = 0;
    }

    Cell_hover(&board->cells[board->selected], 1);
}

/**
 * Moves the current selection
 */
void Board_move(struct Board *board, char dir)
{
    Board_deselect(board);
    switch (dir)
    {
    case 'A':
        board->selected -= board->size;
        break;

    case 'B':
        board->selected += board->size;
        break;

    case 'D':
        board->selected -= 1;
        break;

    case 'C':
        board->selected += 1;
        break;
    }
    Board_select(board);
}

/**
 * Toggle player turn
 */
void Board_toggleTurn(struct Board *board)
{
    board->turn = board->turn == 'X' ? 'O' : 'X';
}

/**
 * Mark the current selected cell
 */
void Board_mark(struct Board *board)
{
    Cell_mark(&board->cells[board->selected], board->turn);
    Board_toggleTurn(board);
}