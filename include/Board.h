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

int i;

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

Cell *Board_getCellAddrsFromXY(Board board, int x, int y)
{
    return &board.cells[board.size * y + x];
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
    if (Cell_mark(&board->cells[board->selected], board->turn))
        Board_toggleTurn(board);
}