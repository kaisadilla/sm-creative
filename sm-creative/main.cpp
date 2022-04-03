#include "main.h"

int main () {
    Assets::loadData();

    Game game;
    game.initialize();

    while (game.isOpen()) {
        game.update();
        game.draw();
        game.lateUpdate();
    }

    return 0;
}