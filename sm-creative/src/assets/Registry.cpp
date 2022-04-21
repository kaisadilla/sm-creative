#include <utils/files.h>

#include "assets/Registry.h"

Registry::Registry (const string& path) {
    std::cout << "=== LOADING ASSET REGISTRY ===" << std::endl;

    string str_registry = utils::readTextFile(path.c_str());
    json json_registry = json::parse(str_registry);

    backgroundImages = json_registry["backgrounds"].get<std::vector<string>>();
    music = json_registry["music"].get<std::vector<string>>();
    tileSize = json_registry["sprites"]["tile_size"];
    tileSprites = json_registry["sprites"]["tiles"].get<std::vector<string>>();
    entitySprites = json_registry["sprites"]["entities"].get<std::vector<string>>();

    int k = 3;
}
