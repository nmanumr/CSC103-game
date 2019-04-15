#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "Board.h"

#define INVERT "\e[7m"
#define RESET "\e[0m"

int i;

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