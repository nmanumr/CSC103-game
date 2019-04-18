// Contains All Game related functions
#include "include/Game.h"

// Main Function
int main()
{
    struct Game game = Game_init();
    Game_startMainLoop(&game);
    return 0;
}