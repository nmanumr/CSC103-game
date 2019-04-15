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

int Game_isWon(struct Game game)
{

    int win = 0, mark, x, y, SIZE = game.board.size;

    //check all rows
    for (x = 0; x < SIZE; x++)
    {
        //mark = board[x][0];
        mark = Board_getCellFromXY(game.board, x, 0).mark;
        for (y = 0; y < SIZE; y++)
        {
            if (Board_getCellFromXY(game.board, x, y).mark == mark)
            {
                win = mark;
            }
            else
            {
                win = 0;
                break;
            }
        }
        if (win != 0)
            break;
    }

    if (win != 0)
    {
        return win;
    }

    //check all coulomns
    for (y = 0; y < SIZE; y++)
    {
        mark = Board_getCellFromXY(game.board, 0, y).mark;
        for (x = 0; x < SIZE; x++)
        {
            if (Board_getCellFromXY(game.board, x, y).mark == mark)
            {
                win = mark;
            }
            else
            {
                win = 0;
                break;
            }
        }
        if (win != 0)
            break;
    }

    if (win != 0)
    {
        return win;
    }

    //check for diagonals
    mark = Board_getCellFromXY(game.board, 0, 0).mark;
    for (x = 0; x < SIZE; x++)
    {
        if (Board_getCellFromXY(game.board, x, x).mark == mark)
        {
            win = mark;
        }
        else
        {
            win = 0;
            break;
        }
    }
    if (win != 0)
    {
        return win;
    }

    mark = Board_getCellFromXY(game.board, SIZE - 1, 0).mark;
    for (x = SIZE - 1; x >= 0; x--)
    {
        if (Board_getCellFromXY(game.board, x, SIZE - x - 1).mark == mark)
        {
            win = mark;
        }
        else
        {
            win = 0;
            break;
        }
    }

    return win;
}

int Game_isDrawn(struct Game game)
{
    int x, y, SIZE = game.board.size;
    for (x = 1; x < SIZE * SIZE; x++)
    {
        if (!isOccupied(x)) //TODO: update
            return 0;
    }
    if (!Game_isWon(game))
    {
        return 1;
    }
    return 1;
}

void Game_renderHeader(struct Game game)
{
    char header[game.width - 13];
    int i;
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