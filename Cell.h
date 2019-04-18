struct Cell
{
    int isEmpty;
    char mark;
    int isHoved;
};

/**
 * Cell Constrctutor
 */
struct Cell Cell_init()
{
    struct Cell cell = {.isEmpty = 1, .mark = ' ', .isHoved = 0};
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

void Cell_hover(struct Cell* cell, int hover)
{
    cell->isHoved = hover;
}