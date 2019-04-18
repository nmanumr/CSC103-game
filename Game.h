#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "Board.h"
#include "conio.h"

#define INVERT "\e[7m"
#define RESET "\e[0m"

#define gotoxy(y, x) fprintf(stdout, "\033[%d;%dH", (y), (x))
#define clear() system("tput reset")

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

char Game_isWon(struct Game *game)
{

    int x, y, SIZE = game->board.size;
    char mark, win;

    //check all rows
    for (x = 0; x < SIZE; x++)
    {
        //mark = board[x][0];
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

int Game_isDrawn(struct Game *game)
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

    //if (!Game_isWon(game))
    //    return 1;
    return 1;
}

void Game_renderHeader(struct Game *game)
{
    printf("%s  Tic Tac Toe%*s%s", INVERT, game->width - 13, " ", RESET);
}

void Game_renderBoard(struct Game *game)
{
    int top = (game->height - 2) / 2 - game->board.size;
    int left = game->width / 2 - (game->board.size / 2) * 4;
    gotoxy(top, left);

    for (i = 0; i < game->board.size; i++)
    {
        for (j = 0; j < game->board.size; j++)
        {
            if (j == 0)
                printf("%s───", i == 0 ? "┌" : "├");
            else
                printf("%s───", i == 0 ? "┬" : "┼");
        }
        printf("%s\n", i == 0 ? "┐" : "┤");
        top++;
        gotoxy(top, left);

        for (j = 0; j < game->board.size; j++)
        {
            struct Cell cell = Board_getCellFromXY(game->board, j, i);
            printf("│ %s%c%s ", (cell.isHoved ? INVERT : RESET), cell.mark, RESET);
        }
        printf("│\n");
        top++;
        gotoxy(top, left);
    }

    for (j = 0; j < game->board.size; j++)
    {
        if (j == 0)
            printf("└───");
        else
            printf("┴───");
    }
    printf("┘\n");
    gotoxy(game->height, 0);
}

void Game_renderKeyMap(struct Game *game)
{
    gotoxy(game->height - 2, 0);
    printf("q: Quit Game\t\tr: Restart Game\t\ts: Save Game\n\
Arrrow Keys: Move Selection\t space: Make Selection\n");
}

void Game_renderInputDialog(struct Game *game, char str[], int *var_addr)
{
    gotoxy(game->height - 3, 0);
    printf("%s %s%*s", INVERT, str, game->width - 21, " ");
    gotoxy(game->height - 3, 22);
    scanf("%d", var_addr);
}

void Game_clearDialog(struct Game *game)
{
    gotoxy(game->height - 3, 0);
    printf("%s%*s", RESET, game->width, " ");
}

void Game_render(struct Game *game)
{
    clear();
    Game_renderHeader(game);
    int size;
    Game_renderInputDialog(game, "Enter size of game: ", &size);
    Game_clearDialog(game);
    game->board = Board_init(size);

    Board_select(&game->board);

    Game_renderBoard(game);
    Game_renderKeyMap(game);
}

/**
 * Checks and return Current Game State
 * @return
 * 0 for Game Continued 
 * 1 for X WON
 * 2 for O WON
 * 3 for Game Draw
 */
int GameState(struct Game *game){
    char win = Game_isWon(game);
    if(win=='X')
        return 1;
    if(win == 'O')
        return 2;
    if(Game_isDrawn(game))
        return 3;
    return 0;
}

/**
 * keep updating throughout the game
 */
void Game_startMainLoop(struct Game *game)
{
    Game_render(game);

    char ch = getch();

    while (ch != 'q' && ch != EOF)
    {
        switch (ch)
        {   
            // Reload/Restart Game
            case 'r':
                Game_render(game);
                break;

            // Handle movements
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                if(GameState(game)==0){
                    Board_move(&game->board, ch);
                    Game_renderBoard(game);
                }else{
                    //Call Action
                }
                break;

            // Mark Selection
            case ' ':
                if(GameState(game)==0){
                    Board_mark(&game->board);
                    Game_renderBoard(game);
                    break;
                }else{
                    // Call Action
                }
        }

        ch = getch();
        fflush(stdin);
    }
}