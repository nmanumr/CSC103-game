#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "Board.h"

#define INVERT "\e[7m"
#define RESET "\e[0m"

#define gotoxy(y, x) printf("\033[%d;%dH", (y), (x))

int i, j;

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

void Game_renderHeader(struct Game game)
{
    char header[game.width - 13];

    for (i = 0; i < game.width - 13; i++)
    {
        header[i] = ' ';
    }

    printf("%s  Tic Tac Toe%s%s", INVERT, header, RESET);
}

void Game_renderBoard(struct Game game)
{
    int top = (game.height - 2) / 2 - game.size;
    int left = game.width / 2 - (game.size / 2) * 4;
    gotoxy(top, left);

    for (i = 0; i < game.size; i++)
    {
        for (j = 0; j < game.size; j++)
        {
            if (j == 0)
                printf("%s───", i == 0 ? "┌" : "├");
            else
                printf("%s───", i == 0 ? "┬" : "┼");
        }
        printf("%s\n", i == 0 ? "┐" : "┤");
        top++;
        gotoxy(top, left);

        for (j = 0; j < game.size; j++)
        {
            printf("│   ");
        }
        printf("│\n");
        top++;
        gotoxy(top, left);
    }

    for (j = 0; j < game.size; j++)
    {
        if (j == 0)
            printf("└───");
        else
            printf("┴───");
    }
    printf("┘\n");
}

void Game_renderKeyMap(struct Game game)
{
    gotoxy(game.height - 1, 0);
    printf("q: Quite Game\t\tr: Restart Game\t\ts: Save Game\n\
Arrrow Keys: Move Selection\t space: Make Selection");
}

void Game_render(struct Game game)
{
    system("clear");
    Game_renderHeader(game);
    Game_renderKeyMap(game);
}

void Game_renderInputDialog(struct Game game, char str[], int *var_addr)
{
    char header[game.width - 31];
    for (i = 0; i < game.width - 31; i++)
        header[i] = ' ';

    gotoxy(game.height - 2, 0);
    printf("%s %s%s", INVERT, str, header);
    gotoxy(game.height - 2, 22);
    scanf("%d", var_addr);
}

void Game_clearDialog(struct Game game)
{
    char header[game.width - 1];
    for (i = 0; i < game.width - 1; i++)
        header[i] = ' ';

    gotoxy(game.height - 2, 0);
    printf("%s%s", RESET, header);
}

void Game_startMainLoop(struct Game game)
{
    Game_render(game);
    int size;
    Game_renderInputDialog(game, "Enter size of game: ", &size);
    Game_clearDialog(game);
    game.size = size;

    Game_renderBoard(game);
    Game_renderKeyMap(game);
    while (1)
    {
    }
}