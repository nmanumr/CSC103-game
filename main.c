#include "include/Game.h"

int main()
{
    struct Game game = Game_init();
    Game_startMainLoop(&game);
    return 0;
}
