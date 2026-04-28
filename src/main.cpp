#include "Core/Game.h"
#include "Resources/ResourceManager.h"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv) {

    ResourceManager::setExecutablePath(argv[0]);

    

    Game game;
    game.init();
    game.run();
    return 0;
}