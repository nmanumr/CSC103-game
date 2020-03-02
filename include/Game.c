#include <time.h>

// Required Files
#include "Board.h"
#include "Game.h"
#include "autoplayer.h"

#ifdef XTERM
#include <sys/ioctl.h>
#include <unistd.h>
#include "Rendererx.h"
#else
#include "Renderer.h"
#endif

int i, j;

/**
 * Game Constructor
 */
Game Game_init()
{
    srand(time(0));
    Game game = {};

#ifdef XTERM
        // To get current window size
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        game.height = w.ws_row;
        game.width = w.ws_col;
#endif

    return game;
}

/**
 * Checks and return Current Game State
 * @return
 * 0 for Game Continued 
 * 1 for X WON
 * 2 for O WON
 * 3 for Game Draw
 */
int GameState(Game *game)
{
    char win = Game_isWon(game);
    if (win == 'X')
        return 1;
    if (win == 'O')
        return 2;
    if (Game_isDrawn(game))
        return 3;
    return 0;
}

/**
 *  Checks for mark won 
 */
char Game_isWon(Game *game)
{

    int x, y, SIZE = game->board.size;
    char mark, win;

    //check all rows
    for (x = 0; x < SIZE; x++)
    {
        mark = Board_getCellFromXY(game->board, x, 0).mark;
        for (y = 0; y < SIZE; y++)
        {
            if (Board_getCellFromXY(game->board, x, y).mark == mark)
            {
                win = mark;
            }
            else
            {
                win = ' ';
                break;
            }
        }
        if (win != ' ')
            break;
    }

    if (win != ' ')
    {
        return win;
    }

    //check all coulomns
    for (y = 0; y < SIZE; y++)
    {
        mark = Board_getCellFromXY(game->board, 0, y).mark;
        for (x = 0; x < SIZE; x++)
        {
            if (Board_getCellFromXY(game->board, x, y).mark == mark)
            {
                win = mark;
            }
            else
            {
                win = ' ';
                break;
            }
        }
        if (win != ' ')
            break;
    }

    if (win != ' ')
    {
        return win;
    }

    //check for diagonals
    mark = Board_getCellFromXY(game->board, 0, 0).mark;
    for (x = 0; x < SIZE; x++)
    {
        if (Board_getCellFromXY(game->board, x, x).mark == mark)
        {
            win = mark;
        }
        else
        {
            win = ' ';
            break;
        }
    }
    if (win != ' ')
    {
        return win;
    }

    mark = Board_getCellFromXY(game->board, SIZE - 1, 0).mark;
    for (x = SIZE - 1; x >= 0; x--)
    {
        if (Board_getCellFromXY(game->board, x, SIZE - x - 1).mark == mark)
        {
            win = mark;
        }
        else
        {
            win = ' ';
            break;
        }
    }

    return win;
}

/**
 *  Checks for Game Draw 
 */
int Game_isDrawn(Game *game)
{
    int x, y, SIZE = game->board.size;
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            if (Board_getCellFromXY(game->board, x, y).isEmpty)
                return 0;
        }
    }

    return 1;
}

/**
 * keep updating throughout the game
 */
void Game_startMainLoop(Game *game)
{
    Game_loop(game);
}