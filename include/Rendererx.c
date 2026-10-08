#ifdef XTERM
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>

// Required Files
#include "Rendererx.h"
#include "Game.h"
#include "conio.h"
#include "autoplayer.h"

int i, j;

/**
 *  Renders the header  
 */
void Game_renderHeader(Game *game)
{
    gotoxy(0, 0);
    printf("%s  Tic Tac Toe%*s%s", INVERT, game->width - 13, " ", RESET);
}

// Screen position of the board's top left corner
#define boardTop(game) (((game)->height - 2) / 2 - (game)->board.size)
#define boardLeft(game) ((game)->width / 2 - ((game)->board.size / 2) * 4)

/**
 *  Renders the Table/board on console 
 */
void Game_renderBoard(Game *game)
{
    int top = boardTop(game);
    int left = boardLeft(game);
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
           "%s space %s Make Selection\t"
           "%s click %s Mark Cell\n",
           INVERT, RESET, INVERT, RESET, INVERT, RESET, INVERT, RESET, INVERT, RESET);
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

// Rows taken by the won/drawn banners
#define BANNER_HEIGHT 8

/**
 *  Returns the first row for an end banner of given width so it
 *  doesn't cover the board, or -1 if there is no room above or below it
 */
int Game_bannerRow(Game *game, int width)
{
    int top = boardTop(game);
    int bottom = top + game->board.size * 2;

    if (game->width < width)
        return -1;
    // below the header, above the board
    if (top - BANNER_HEIGHT >= 2)
        return top - BANNER_HEIGHT;
    // below the board, above the keymap
    if (bottom + BANNER_HEIGHT <= game->height - 2)
        return bottom + 1;
    return -1;
}

/**
 *  Renders a one line result in the header when the banner doesn't fit
 */
void Game_renderResultLine(Game *game, char *bg, char *text)
{
    gotoxy(1, game->width / 2 - (int)strlen(text) / 2);
    printf("%s%s%s", bg, text, RESET);
    gotoxy(game->height, 0);
}

/**
 *  Renders Mark won Splash 
 */
void Game_renderWon(Game *game, char player)
{
    int top = Game_bannerRow(game, 46) + 1;
    int left = (game->width) / 2 - 20;
    if (top == 0)
    {
        Game_renderResultLine(game, player == 'X' ? RED_BG : YLOW_BG, player == 'X' ? " X WON " : " O WON ");
        return;
    }
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
    int top = Game_bannerRow(game, 40) + 1;
    int left = (game->width) / 2 - 18;
    if (top == 0)
    {
        Game_renderResultLine(game, "\e[44m", " DRAW ");
        return;
    }
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
 *  Renders the game screen with the current board
 */
void Game_renderScreen(Game *game)
{
    clear();
    Game_renderHeader(game);
    Game_renderTurn(game);
    Game_renderBoard(game);
    Game_renderKeyMap(game);
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

    game->comPlayer = compPlayer == 1 ? 1 : 0;
    game->board = Board_init(size);

    Board_select(&game->board);
    Game_renderScreen(game);
}

/**
 *  Restarts the game with the last used settings
 */
void Game_restart(Game *game)
{
    int size = game->board.size;
    free(game->board.cells);
    game->board = Board_init(size);

    Board_select(&game->board);
    Game_renderScreen(game);
}

void sizeFix(Game *game)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if ((game->height != w.ws_row) || (game->width != w.ws_col))
    {
        game->height = w.ws_row;
        game->width = w.ws_col;
        Game_renderScreen(game);
    }
}

/**
 *  Reads a key, decoding arrow keys and mouse clicks
 *  @return arrow keys as 'A'-'D', KEY_CLICK for a left click
 *  (position in mouseX, mouseY), 0 for other mouse events
 */
char Game_readKey(int *mouseX, int *mouseY)
{
    char ch = getch();
    if (ch != '\e')
        return ch;

    ch = getch();
    if (ch != '[')
        return ch;

    ch = getch();
    if (ch != '<')
        return ch;

    // SGR mouse report: ESC [ < button ; x ; y (M = press, m = release)
    int button = 0, x = 0, y = 0;
    while ((ch = getch()) >= '0' && ch <= '9')
        button = button * 10 + ch - '0';
    while ((ch = getch()) >= '0' && ch <= '9')
        x = x * 10 + ch - '0';
    while ((ch = getch()) >= '0' && ch <= '9')
        y = y * 10 + ch - '0';

    if (ch == 'M' && button == 0)
    {
        *mouseX = x;
        *mouseY = y;
        return KEY_CLICK;
    }
    return 0;
}

/**
 *  Returns the cell index at screen position x, y or -1
 */
int Game_cellAt(Game *game, int x, int y)
{
    int row = y - boardTop(game);
    int col = x - boardLeft(game);

    // skip the border lines
    if (row < 0 || col < 0 || row % 2 == 0 || col % 4 == 0)
        return -1;

    row /= 2;
    col /= 4;
    if (row >= game->board.size || col >= game->board.size)
        return -1;

    return row * game->board.size + col;
}

/**
 *  Turns off mouse reporting so the terminal is left usable
 */
void Game_disableMouse()
{
    write(STDOUT_FILENO, MOUSE_OFF, sizeof(MOUSE_OFF) - 1);
}

void Game_onInterrupt(int sig)
{
    Game_disableMouse();
    _exit(1);
}


void Game_loop(Game *game)
{
    Game_render(game);

    fflush(stdout);
    printf(MOUSE_ON);
    signal(SIGINT, Game_onInterrupt);

    int mouseX, mouseY, cell;
    char ch = Game_readKey(&mouseX, &mouseY);
    fflush(stdin);

    int gameS = 0;

    while (ch != 'q' && ch != EOF)
    {
        sizeFix(game);

        switch (ch)
        {
            // Reload/Restart Game
            case 'r':
                Game_restart(game);
                break;

                // Handle movements
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                if (gameS == 0)
                {
                    Board_move(&game->board, ch);
                    Game_renderBoard(game);
                }
                break;

                // Mark Selection
            case ' ':
                if (gameS == 0)
                {
                    Board_mark(&game->board);
                    Game_renderBoard(game);
                    Game_renderTurn(game);
                }
                break;

                // Mark clicked cell
            case KEY_CLICK:
                cell = Game_cellAt(game, mouseX, mouseY);
                if (gameS == 0 && cell >= 0)
                {
                    Board_selectAt(&game->board, cell);
                    Board_mark(&game->board);
                    Game_renderBoard(game);
                    Game_renderTurn(game);
                }
                break;
        }

        gameS = GameState(game);
        switch (gameS)
        {
            case 1:
                Game_renderWon(game, 'X');
                break;
            case 2:
                Game_renderWon(game, 'O');
                break;
            case 3:
                Game_renderDrawn(game);
                break;
        }

        if (game->board.turn == 'O' && gameS == 0 && game->comPlayer)
        {
            markBestMove(&game->board, game->height, game->width);
            Game_renderBoard(game);
            Game_renderTurn(game);

            continue;
        }

        ch = Game_readKey(&mouseX, &mouseY);
        fflush(stdin);
    }

    Game_disableMouse();
}

#endif
