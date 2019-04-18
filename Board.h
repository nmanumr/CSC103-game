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

    struct Board board = {.size = size, .cells = cells, .selected = 0};
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
 * 
 * @param dir
 */
void Board_move(struct Board *board, char dir)
{
    Board_deselect(board);
    switch (dir)
    {
    case 't':
        board->selected -= board->size;
        break;

    case 'b':
        board->selected += board->size;
        break;

    case 'l':
        board->selected -= 1;
        break;

    case 'r':
        board->selected += 1;
        break;
    }
    Board_select(board);
}