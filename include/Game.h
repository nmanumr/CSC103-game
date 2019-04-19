#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Required Files
#include "Board.h"
#include "conio.h"

// Colors defined
#define INVERT "\e[7m"
#define RESET "\e[0m"

#define gotoxy(y, x) fprintf(stdout, "\033[%d;%dH", (y), (x))
#define clear() system("tput reset")

int i, j;

typedef struct
{
    Board board;
    int height;
    int width;
}Game;

/**
 * Game Constructor
 */
Game Game_init()
{
    // To get current window size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    Game game = {.height = w.ws_row, .width = w.ws_col};

    return game;
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
 *  Renders the header  
 */
void Game_renderHeader(Game *game)
{
    gotoxy(0,0);
    printf("%s  Tic Tac Toe%*s%s", INVERT, game->width - 13, " ", RESET);
}

/**
 *  Renders the Table/board on console 
 */
void Game_renderBoard(Game *game)
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
            Cell cell = Board_getCellFromXY(game->board, j, i);
            printf("│ %s%c%s ", (cell.isHovered ? INVERT : RESET), cell.mark, RESET);
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

/**
 *  Renders Footer/KeyNotes 
 */
void Game_renderKeyMap(Game *game)
{
    gotoxy(game->height - 1, 0);
    printf("%s q %s Quit Game\t"
        "%s r %s Restart Game\t"
        "%s Arrow Keys %s Move Selection\t"
        "%s space %s Make Selection\n"
        ,INVERT,RESET,INVERT,RESET,INVERT,RESET,INVERT,RESET);
}
/**
 *  Renders the Enteries on table/board 
 */
void Game_renderInputDialog(Game *game, char str[], int *var_addr)
{
    gotoxy(game->height - 3, 0);
    printf("%s %s%*s", INVERT, str, game->width - 21, " ");
    gotoxy(game->height - 3, 22);
    scanf("%d", var_addr);
}

void Game_renderSplash(Game *game){
    int top = (game->height - 2) / 2 - 3;
    int left = (game->width) / 2 - 25;
    gotoxy(top - 1, left);
    printf("╔═══════════════════════════════════════════════════╗");
    gotoxy(top, left);
    printf("║ %s ║", TTT1);
    gotoxy(top + 1, left);
    printf("║ %s ║", TTT2);
    gotoxy(top + 2, left);
    printf("║ %s ║", TTT3);
    gotoxy(top + 3, left);
    printf("║ %s ║", TTT4);
    gotoxy(top + 4, left);
    printf("║ %s ║", TTT5);
    gotoxy(top + 5, left);
    printf("║ %s ║", TTT6);
    gotoxy(top + 6,left);
    printf("║───────────────────────────────────────────────────║");
    gotoxy(top + 7,left);
    printf("║ Created by:                         Nauman Umer & ║");
    gotoxy(top + 8, left);
    printf("║                                Ameer Hamza Naveed ║");
    gotoxy(top + 9,left);
    printf("╚═══════════════════════════════════════════════════╝");
    gotoxy(game->height, 0);
}

/**
 *  Renders Mark won Splash 
 */
void Game_renderWon(Game *game, char player)
{
    int top = (game->height - 2) / 2 - 3;
    int left = (game->width) / 2 - 20;
    gotoxy(top - 1, left);
    printf("╔════════════════════════════════════════════╗");
    gotoxy(top, left);
    printf("║ %s    %s ║", player == 'X' ? XL1 : OL1, WONL1);
    gotoxy(top + 1, left);
    printf("║ %s    %s ║", player == 'X' ? XL2 : OL2, WONL2);
    gotoxy(top + 2, left);
    printf("║ %s    %s ║", player == 'X' ? XL3 : OL3, WONL3);
    gotoxy(top + 3, left);
    printf("║ %s    %s ║", player == 'X' ? XL4 : OL4, WONL4);
    gotoxy(top + 4, left);
    printf("║ %s    %s ║", player == 'X' ? XL5 : OL5, WONL5);
    gotoxy(top + 5, left);
    printf("║ %s    %s ║", player == 'X' ? XL6 : OL6, WONL6);
    gotoxy(top + 6, left);
    printf("╚════════════════════════════════════════════╝");
    gotoxy(game->height, 0);
}

/**
 *  renders Drawn Splash 
 */
void Game_renderDrawn(Game *game)
{
    int top = (game->height - 2) / 2 - 3;
    int left = (game->width) / 2 - 18;
    gotoxy(top - 1, left);
    printf("╔══════════════════════════════════════╗");
    gotoxy(top, left);
    printf("║ %s ║", DRAW_L1);
    gotoxy(top + 1, left);
    printf("║ %s ║", DRAW_L2);
    gotoxy(top + 2, left);
    printf("║ %s ║", DRAW_L3);
    gotoxy(top + 3, left);
    printf("║ %s ║", DRAW_L4);
    gotoxy(top + 4, left);
    printf("║ %s ║", DRAW_L5);
    gotoxy(top + 5, left);
    printf("║ %s ║", DRAW_L6);
    gotoxy(top + 6, left);
    printf("╚══════════════════════════════════════╝");
    gotoxy(game->height, 0);
}

/**
 *  clears size input dialog
 */
void Game_clearDialog(Game *game)
{
    gotoxy(game->height - 3, 0);
    printf("%s%*s", RESET, game->width, " ");
}

/**
 *  Renders the complete game 
 */
void Game_render(Game *game)
{
    clear();
    Game_renderSplash(game);
    int size;
    Game_renderInputDialog(game, "Enter size of game: ", &size);
    Game_clearDialog(game);
    clear();
    Game_renderHeader(game);
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
int GameState(Game *game){
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
void Game_startMainLoop(Game *game)
{
    Game_render(game);

    char ch = getch();

    int gameS = 0;

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
                if(gameS==0){
                    Board_move(&game->board, ch);
                    Game_renderBoard(game);
                }
                break;

            // Mark Selection
            case ' ':
                if(gameS==0){
                    Board_mark(&game->board);
                    Game_renderBoard(game);
                }
                break;
        }

        gameS = GameState(game);
        switch(gameS){
            case 1:
                Game_renderWon(game,'X');
                break;
            case 2:
                Game_renderWon(game, 'O');
                break;
            case 3:
                Game_renderDrawn(game);
                break;
        }
        ch = getch();
        fflush(stdin);
    }
}