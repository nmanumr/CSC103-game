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

void Board_deselect(Board board)
{
    board.cells[board.selected].isHoved = 0;
}

void Board_select(Board board)
{
    if (board.selected >= board.size * board.size)
    {
        board.selected = board.size * board.size - 1;
    }
    else if (board.selected < 0)
    {
        board.selected = 0;
    }
}

/**
 * Moves the current selection
 * 
 * @param dir
 */
void Board_move(Board board, char dir){
    Board_deselect(board);
    switch (dir)
    {
        case 't':
            board.selected -= board.size;
            break;

        case 'b':
            board.selected += board.size;
            break;

        case 'l':
            board.selected -= 1;
            break;
        
        case 'r':
            board.selected += 1;
            break;
    }
    Board_select(board);
}