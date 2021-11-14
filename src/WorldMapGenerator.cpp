/*********************************************************
** Project: Cube Builder Game
** File: WorldMapGenerator.cpp
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Implements WorldMapGenerator.h
***********************************************************/

#include "WorldMapGenerator.h"

WorldMapGenerator::WorldMapGenerator() {}

WorldMap* WorldMapGenerator::generateWorld(game::WORLD_MAP_SEED seed) {
    if (seed == game::BASIC_SMALL) return basic1Small();
    else if (seed == game::BASIC_MEDIUM) return basic1Medium();
    else if (seed == game::BASIC_LARGE) return basicLarge();
    return nullptr;
}

WorldMap* WorldMapGenerator::basic1Small() {
    //  1 X 1 size
    WorldMap* worldmap = new WorldMap(1);
    worldmap->addSlab(new GrassSlab);
    return worldmap;
}

WorldMap* WorldMapGenerator::basic1Medium() {
    //  3 x 3 world size
    WorldMap* worldmap = new WorldMap(3);

    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    return worldmap;
}

WorldMap* WorldMapGenerator::basicLarge() {
    // 9 x 9 world size
    WorldMap* worldmap = new WorldMap(9);

    //  1
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    //  2
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    // 3
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    // 4
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    //  5
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    //  6
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    //  7
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    //  8
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    //  9
    worldmap->addSlab(new GrassSlab);  //  1
    worldmap->addSlab(new GrassSlab);  //  2
    worldmap->addSlab(new GrassSlab);  //  3
    worldmap->addSlab(new WoodlandSlab);  //  4
    worldmap->addSlab(new GrassSlab);  //  5
    worldmap->addSlab(new GrassSlab);  //  6
    worldmap->addSlab(new GrassSlab);  // 7
    worldmap->addSlab(new GrassSlab); // 8
    worldmap->addSlab(new WoodlandSlab);  // 9

    return worldmap;
}
