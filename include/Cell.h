struct Cell
{
    int isEmpty;
    char mark;
    int isHovered;
};

/**
 * Cell Constrctutor
 */
struct Cell Cell_init()
{
    struct Cell cell = {.isEmpty = 1, .mark = ' ', .isHovered = 0};
    return cell;
}

/**
 * Marks a cell with X or O and set it as non-empty
 */
void Cell_mark(struct Cell *cell, char mark)
{
    if(cell->isEmpty){
        cell->mark = mark;
        cell->isEmpty = 0;
    }
}

/**
 *  Mark cell hovered 
 */
void Cell_hover(struct Cell* cell, int isHovered)
{
    cell->isHovered = isHovered;
}