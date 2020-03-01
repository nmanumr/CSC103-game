#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

// Required Files
#include "Renderer.h"
#include "Game.h"

int i, j;

/**
 *  Renders the header  
 */
void Game_renderHeader(Game *game)
{
    gotoxy(0, 0);
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

            if (cell.mark == 'X')
                printf("│ %s%sX%s ", (cell.isHovered ? INVERT : RESET), RED_FG, RESET);
            else if (cell.mark == 'O')
                printf("│ %s%sO%s ", (cell.isHovered ? INVERT : RESET), YLOW_FG, RESET);
            else
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
           "%s space %s Make Selection\n",
           INVERT, RESET, INVERT, RESET, INVERT, RESET, INVERT, RESET);
}
/**
 *  Renders the Enteries on table/board 
 */
void Game_renderInputDialog(Game *game, char str[], int *var_addr)
{
    gotoxy(game->height - 3, 0);
    printf("%s %s%*s", INVERT, str, (int)game->width - (int)strlen(str) - 1, " ");
    gotoxy(game->height - 3, (int)strlen(str) + 2);
    scanf("%d", var_addr);
}

void Game_renderSplash(Game *game)
{
    int top = (game->height - 2) / 2 - 4;
    int left = (game->width) / 2 - 26;
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
    gotoxy(top + 6, left);
    printf("╟───────────────────────────────────────────────────╢");
    gotoxy(top + 7, left);
    printf("║ \e[2mCreated by:\e[0m                  \e[1m\e[4mAmeer Hamza Naveed\e[0m \e[2m&\e[0m ║");
    gotoxy(top + 8, left);
    printf("║                                     \e[1m\e[4mNauman Umer\e[0m   ║");
    gotoxy(top + 9, left);
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

void Game_renderTurn(Game *game)
{
    gotoxy(1, game->width - 10);
    if (game->board.turn == 'X')
        printf("%s%s%sTurn: X %s", INVERT, BLINK, RED_BG, RESET);
    else
        printf("%s%s%sTurn: O %s", INVERT, BLINK, YLOW_BG, RESET);
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
    int size, compPlayer = 0;
    Game_renderInputDialog(game, "Enter size of game: ", &size);
    Game_clearDialog(game);
    // Asking for computer player
    if (size == 3)
        Game_renderInputDialog(game, "Do you wanna play again computer (0/1): ", &compPlayer);

    clear();
    Game_renderHeader(game);

    game->comPlayer = compPlayer == 1 ? 1 : 0;
    game->board = Board_init(size);

    Board_select(&game->board);

    Game_renderBoard(game);
    Game_renderKeyMap(game);
    Game_renderTurn(game);
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

void sizeFix(Game *game)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if ((game->height != w.ws_row) || (game->width != w.ws_col))
    {
        game->height = w.ws_row;
        game->width = w.ws_col;
        clear();
        Game_renderHeader(game);
        Game_renderTurn(game);
        Game_renderBoard(game);
        Game_renderKeyMap(game);
    }
}
