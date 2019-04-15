#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define INVERT "\e[7m"
#define RESET "\e[0m"

int i;

///////////////
// Cell Class
///////////////

struct Cell
{
    int isEmpty;
    char mark;
};

/**
 * Cell Constrctutor
 */
struct Cell Cell_init()
{
    struct Cell cell = {.isEmpty = 1, .mark = '\0'};
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

/////////////////
// Board Class
/////////////////

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
    int i = 0;
    for (; i < size * size; i++)
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

/////////////////
// Game Class
/////////////////

struct Game
{
    struct Board board;
    int size;
    int height;
    int width;
};

struct Game Game_init()
{
    // To get current window size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    struct Game game = {.height = w.ws_row, .width = w.ws_col};

    return game;
}

void Game_startMainLoop(struct Game game)
{
    while (1)
    {
        // TODO:
        continue;
    }
}

void Game_renderHeader(struct Game game)
{
    char header[game.width - 13];

    for (i = 0; i < game.width - 13; i++)
    {
        header[i] = ' ';
    }

    printf("%s  Tic Tac Toe%s%s", INVERT, header, RESET);
}

void Game_renderKeyMap(struct Game game)
{
}

void Game_render(struct Game game)
{
    system("clear");
    Game_renderHeader(game);
    Game_renderKeyMap(game);
}

////////////////////
// main function
///////////////////

int main()
{
    struct Game game = Game_init();
    Game_render(game);
    return 0;
}
