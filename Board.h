#include "Cell.h"

int i;

struct Board
{
    int size;
    struct Cell *cells;
    char turn;
};

/**
 * Board Constructor
 */
struct Board Board_init(int size)
{
    struct Cell cells[size * size];

    // intialize cells array mein empty Cell as variable
    // array intialization is not supported
    for (i = 0; i < size * size; i++)
    {
        cells[i] = Cell_init();
    }

    struct Board board = {.size = size, .cells = cells};
    return board;
}

/**
 * Returns a cell from given XY position
 */
struct Cell Board_getCellFromXY(struct Board board, int x, int y)
{
    return board.cells[board.size * y + x];
}