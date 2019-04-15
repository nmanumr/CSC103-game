#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "Board.h"

#define INVERT "\e[7m"
#define RESET "\e[0m"

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
    int i;
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

int Game_isWon(struct Game game){

    int win = 0, mark,x,y,SIZE = game.board.size;

    //check all rows
    for(x=0; x<SIZE; x++){
        //mark = board[x][0];
        mark = Board_getCellFromXY(game.board, x,0).mark;
        for(y=0; y<SIZE; y++){
            if(Board_getCellFromXY(game.board, x,y).mark==mark){
                win = mark;
            }else{
                win = 0;
                break;
            }
        }
        if(win!=0)
            break;
    }

    if(win != 0){
        return win;
    }
    

    //check all coulomns
    for(y=0; y<SIZE; y++){
        mark = Board_getCellFromXY(game.board, 0,y).mark;
        for(x=0; x<SIZE; x++){
            if(Board_getCellFromXY(game.board, x,y).mark==mark){
                win = mark;
            }else{
                win = 0;
                break;
            }
        }
        if(win!=0)
            break;
    }

    if(win != 0){
        return win;
    }

    //check for diagonals
    mark = Board_getCellFromXY(game.board, 0,0).mark;
    for(x=0;x<SIZE;x++){
        if(Board_getCellFromXY(game.board, x,x).mark==mark){
            win = mark;
        }else{
            win = 0;
            break;
        }
    }
    if(win != 0){
        return win;
    }

    mark = Board_getCellFromXY(game.board, SIZE-1,0).mark;
    for(x=SIZE-1;x>=0;x--){
        if(Board_getCellFromXY(game.board, x,SIZE-x-1).mark==mark){
            win = mark;
        }else{
            win = 0;
            break;
        }
    }

    return win;
}

int Game_isDrawn(struct Game game){
    int x, y, SIZE = game.board.size;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(Board_getCellFromXY(game.board, x,y).isEmpty)
                return 0;
        }
    }
    if(!Game_isWon(game)){
        return 1;
    }
    return 1;
}