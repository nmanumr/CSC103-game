#if !defined(XTERM)
#include <stdio.h>

#include "Game.h"
#include "Board.h"
#include "Renderer.h"
#include "autoplayer.h"

int i, j;

void Game_renderSplash(Game *game)
{
    printf("%s\n", TTTN1);
    printf("%s\n", TTTN2);
    printf("%s\n", TTTN3);
    printf("%s\n", TTTN4);
    printf("%s\n", TTTN5);
    printf("%s\n", TTTN6);
    printf("%s\n", TTTN7);
    printf("%s\n", TTTN8);
    printf("%s\n", TTTN9);
    printf("%s\n", TTTN10);
    printf("%s\n", TTTN11);
}

void Game_renderWon(Game *game, char player)
{
    printf("\n\n%c Won\n\n", player);
}

void Game_renderDrawn(Game *game)
{
    printf("\n\nGame Draw\n\n");
}

/**
 *  Renders the Table/board on console 
 */
void Game_renderBoard(Game *game)
{
    printf("\n");
    for (i = 0; i < game->board.size * 2; i++)
    {
        if (i % 2 == 0)
        {
            for (j = 0; j < game->board.size; j++)
            {
                if (j == 0)
                    printf("%s───", i == 0 ? "┌" : "├");
                else
                    printf("%s───", i == 0 ? "┬" : "┼");
            }
            printf("%s\n", i == 0 ? "┐" : "┤");
        }
        else
        {
            for (j = 0; j < game->board.size; j++)
            {
                Cell cell = Board_getCellFromXY(game->board, j, i / 2);
                if (cell.mark == 'O' || cell.mark == 'X')
                    printf("│ %c ", cell.mark);
                else
                    printf("│ %d ", i / 2 * game->board.size + j + 1);
            }
            printf("│\n");
        }
    }

    for (j = 0; j < game->board.size; j++)
    {
        if (j == 0)
            printf("└───");
        else
            printf("┴───");
    }
    printf("┘\n\n");
}

void Game_renderMenu()
{
    printf("1-9: For selection\nq: Quit Game\n: ");
}

void Game_renderTurn(Game *game)
{
    printf("Turn: %c\n", game->board.turn);
}

/**
 *  Renders the complete game 
 */
void Game_render(Game *game)
{
    Game_renderSplash(game);
    int size = 3, compPlayer = 0;
    // printf("\n\nEnter size of the game: ");
    // scanf("%d", &size);

    if (size == 3)
    {
        printf("Do you wanna play again computer (0/1): ");
        scanf("%d", &compPlayer);
    }

    game->comPlayer = compPlayer == 1 ? 1 : 0;
    game->board = Board_init(size);

    Game_renderBoard(game);
    Game_renderTurn(game);
    Game_renderMenu();
}

void Game_loop(Game *game)
{
    Game_render(game);

    int ch, gameS = 0, shouldPrintMenu = 1;

    fflush(stdin);
    scanf(" %c", &ch);

    do
    {
        if (ch > '0' && ch <= '9')
        {
            int selected = Board_markAt(&game->board, ch - 49);
            if (!selected){
                printf("Cell already marked\n: ");
                shouldPrintMenu = 0;
            }
            else
            {
                Game_renderBoard(game);
                Game_renderTurn(game);
            }
        }
        else if (ch == 'q')
        {
            break;
        }
        else
        {
            printf("Invalid input, try again \n: ");
        }

        gameS = GameState(game);
        if (gameS == 1)
        {
            Game_renderWon(game, 'X');
            break;
        }
        else if (gameS == 2)
        {
            Game_renderWon(game, 'O');
            break;
        }
        else if (gameS == 3)
        {
            Game_renderDrawn(game);
            break;
        }

        if (game->board.turn == 'O' && gameS == 0 && game->comPlayer)
        {
            markBestMove(&game->board, game->height, game->width);
            Game_renderBoard(game);
            Game_renderTurn(game);
            Game_renderMenu();
        }
        else if(shouldPrintMenu)
        {
            Game_renderMenu();
        }

        scanf(" %c", &ch);
        shouldPrintMenu = 1;
    } while (1);
}
#endif
