#pragma once

typedef struct
{
    int isEmpty;
    char mark;
    int isHovered;
} Cell;

/**
 * Cell Constrctutor
 */
Cell Cell_init();

/**
 * Marks a cell with X or O and set it as non-empty
 */
int Cell_mark(Cell *cell, char mark);

/**
 *  Mark cell hovered 
 */
void Cell_hover(Cell *cell, int isHovered);
