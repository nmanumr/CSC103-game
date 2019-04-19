#include <stdlib.h>

#include "Cell.h"

#define DRAW_L1 " ██████╗ ██████╗  █████╗ ██╗    ██╗ "
#define DRAW_L2 " ██╔══██╗██╔══██╗██╔══██╗██║    ██║ "
#define DRAW_L3 " ██║  ██║██████╔╝███████║██║ █╗ ██║ "
#define DRAW_L4 " ██║  ██║██╔══██╗██╔══██║██║███╗██║ "
#define DRAW_L5 " ██████╔╝██║  ██║██║  ██║╚███╔███╔╝ "
#define DRAW_L6 " ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝  "

#define WONL1 "██╗    ██╗ ██████╗ ███╗   ██╗"
#define WONL2 "██║    ██║██╔═══██╗████╗  ██║"
#define WONL3 "██║ █╗ ██║██║   ██║██╔██╗ ██║"
#define WONL4 "██║███╗██║██║   ██║██║╚██╗██║"
#define WONL5 "╚███╔███╔╝╚██████╔╝██║ ╚████║"
#define WONL6 " ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝"

#define XL1 " ██╗  ██╗"
#define XL2 " ╚██╗██╔╝"
#define XL3 "  ╚███╔╝ "
#define XL4 "  ██╔██╗ "
#define XL5 " ██╔╝ ██╗"
#define XL6 " ╚═╝  ╚═╝"

#define OL1 " ██████╗ "
#define OL2 "██╔═══██╗"
#define OL3 "██║   ██║"
#define OL4 "██║   ██║"
#define OL5 "╚██████╔╝"
#define OL6 " ╚═════╝ "

#define TTT1 "██████████╗ ██████████╗     ██████████╗   ██████╗"
#define TTT2 "╚═══██╔═══╝ ╚═══██╔═══╝     ╚═══██╔═══╝   ██╔═══╝"
#define TTT3 "    ██║██╗ ████╗██║██████╗ ████╗██║██████╗██████╗" 
#define TTT4 "    ██║██║██╔══╝██║██║ ██║██╔══╝██║██║ ██║██╔═══╝"
#define TTT5 "    ██║██║╚████╗██║███████╗████╗██║██████║██████╗"
#define TTT6 "    ╚═╝╚═╝ ╚═══╝╚═╝╚══════╝╚═══╝╚═╝╚═════╝╚═════╝" 

int i;

typedef struct 
{
    int size;
    Cell *cells;
    char turn;
    int selected;
}Board;

/**
 * Board Constructor
 */
Board Board_init(int size)
{
    Cell *cells = malloc(sizeof(Cell_init()) * size * size);

    // intialize cells array mein empty Cell as variable
    // array intialization is not supported
    for (i = 0; i < size * size; i++)
    {
        cells[i] = Cell_init();
    }

    Board board = {.size = size, .cells = cells, .selected = 0, .turn = 'X'};
    return board;
}

/**
 * Returns a cell from given XY position
 */
Cell Board_getCellFromXY(Board board, int x, int y)
{
    return board.cells[board.size * y + x];
}

/**
 *  Removes the hover mark
 */
void Board_deselect(Board *board)
{
    board->cells[board->selected].isHovered = 0;
}

/**
 *  mark cell hovered 
 */
void Board_select(Board *board)
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
void Board_move(Board *board, char dir)
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
void Board_toggleTurn(Board *board)
{
    board->turn = board->turn == 'X' ? 'O' : 'X';
}

/**
 * Mark the current selected cell
 */
void Board_mark(Board *board)
{
    if(Cell_mark(&board->cells[board->selected], board->turn))
        Board_toggleTurn(board);
}