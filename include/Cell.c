#include "Cell.h"

/**
 * Cell Constrctutor
 */
Cell Cell_init()
{
    Cell cell = {.isEmpty = 1, .mark = ' ', .isHovered = 0};
    return cell;
}

/**
 * Marks a cell with X or O and set it as non-empty
 */
int Cell_mark(Cell *cell, char mark)
{
    if (cell->isEmpty)
    {
        cell->mark = mark;
        cell->isEmpty = 0;
        return 1;
    }
    return 0;
}

/**
 *  Mark cell hovered 
 */
void Cell_hover(Cell *cell, int isHovered)
{
    cell->isHovered = isHovered;
}
