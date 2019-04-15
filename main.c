#include "Game.h"

int main()
{
    struct Game game = Game_init();
    Game_render(game);
    return 0;
}
