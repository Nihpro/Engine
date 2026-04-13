#include "Core/Game.h"
#include "Resources/ResourceManager.h"
#include <filesystem>

int main(int argc, char** argv) {

    ResourceManager::setExecutablePath(argv[0]);

    Game game;
    game.run();
    return 0;
}