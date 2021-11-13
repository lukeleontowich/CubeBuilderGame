#include "WorldMapGenerator.h"

WorldMapGenerator::WorldMapGenerator() {}

WorldMap* WorldMapGenerator::generateWorld(game::WORLD_MAP_SEED seed) {
    if (seed == game::BASIC_SMALL) return basic1Small();
    return nullptr;
}

WorldMap* WorldMapGenerator::basic1Small() {
    //  3 x 3 world size
    WorldMap* worldmap = new WorldMap(3);

    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new WoodlandSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new WoodlandSlab); // 8
    worldmap->addSlab(new WoodlandSlab);
    return worldmap;
}

