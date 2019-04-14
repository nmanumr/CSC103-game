#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3
#define CS "clear"

int board[SIZE][SIZE] = {0, 0};
int turn, x, y;

void drawBoard();
char mark(int);
int generateRandom();
void getMove();
int getX(int);
int getY(int);
int isWon();
int isDraw();
int isOccupied(int);

int main()
{
    system(CS);
    drawBoard();
    turn = generateRandom();
    while (!isWon() && !isDraw())
    {
        getMove();
        drawBoard();
    }
    if (isDraw())
        printf("Game Draw\n");
    else
    {
        printf("%c Won the Game!\n", (isWon() == 1 ? 'X' : 'O'));
    }

    return 0;
}


/**
 * Draw the current board
 */
void drawBoard()
{
    printf("\n");
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            if (board[x][y] != 0)
                printf(" %-2c", mark(board[x][y]));
            else
                printf(" %-2d", y + (x * SIZE) + 1);
            if (!(y == SIZE - 1))
                printf("|");
        }
        printf("\n");
        int lineSize = (4 * SIZE) - 1;
        if (!(x == SIZE - 1))
            for (y = 0; y < lineSize; y++)
            {
                printf("-");
            }
        printf("\n");
    }
    printf("\n\n");
}


/**
 * Return a random number between 0-1
 */
int generateRandom()
{
    srand(time(0));
    return (int)rand() % 2 + 1;
}


/**
 * shift the turn from X to O
 */
int shiftTurn()
{
    turn = turn == 1 ? 2 : 1;
}


/**
 * Return mark from turn number
 */
char mark(int M)
{
    switch (M)
    {
    case 1:
        return 'X';
        break;

    case 2:
        return 'O';
        break;

    default:
        return '?';
        break;
    }
}


/**
 * Input a move from user
 */
void getMove()
{
    int maxRange = SIZE * SIZE;
    int value;
    do
    {
        printf("\n%c\'s turn, Enter your choice: ", mark(turn));
        scanf("%d", &value);
        fflush(stdin);
        if (value > maxRange || value < 1)
        {
            printf("\nWrong Selection! choose between 1-%d\n", maxRange);
        }
        else
        {
            system(CS);
            if (isOccupied(value))
            {
                printf("\nAlready Occupied.! choose another!\n");
            }
            else
            {
                board[getX(value)][getY(value)] = turn;
                shiftTurn();
            }
        }
    } while (value > maxRange || value < 1);
}


/**
 * Calculate x compoennt of given position
 */
int getX(int value)
{
    y = 0;
    while (value > SIZE)
    {
        value -= SIZE;
        y++;
    }
    return y;
}


/**
 * Calculate y compoennt of given position
 */
int getY(int value)
{
    while (value > SIZE)
        value -= SIZE;
    return --value;
}


/**
 * Check if a specific position is already occupied or not
 */ 
int isOccupied(int pos)
{
    return (board[getX(pos)][getY(pos)] != 0) ? 1 : 0;
}


/**
 * Return 1 if X won else 0
 */
int isWon()
{

    int win = 0, mark;

    //check all rows
    for (x = 0; x < SIZE; x++)
    {
        mark = board[x][0];
        for (y = 0; y < SIZE; y++)
        {
            if (board[x][y] == mark)
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
        mark = board[0][y];
        for (x = 0; x < SIZE; x++)
        {
            if (board[x][y] == mark)
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
    mark = board[0][0];
    for (x = 0; x < SIZE; x++)
    {
        if (board[x][x] == mark)
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

    mark = board[SIZE - 1][0];
    for (x = SIZE - 1; x >= 0; x--)
    {
        if (board[x][SIZE - x - 1] == mark)
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


/**
 * Return 1 if game drawn else 0
 */
int isDraw()
{
    for (x = 1; x <= SIZE * SIZE; x++)
    {
        if (!isOccupied(x))
            return 0;
    }
    if (!isWon())
    {
        return 1;
    }
    return 1;
}
