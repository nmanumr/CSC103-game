// Contains All Game related functions
#include "include/Game.h"

// Main Function
int main()
{
    Game game = Game_init();
    Game_startMainLoop(&game);
    return 0;
}