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
    struct Cell cell = {.isEmpty = 1, .mark = '\0', .isHoved = 0};
    return cell;
}

/**
 * Marks a cell with X or O and set it as non-empty
 */
void Cell_markCell(struct Cell cell, char mark)
{
    cell.mark = mark;
    cell.isEmpty = 0;
}

void Cell_hover(struct Cell cell, int hover)
{
    cell.isHoved = hover;
}