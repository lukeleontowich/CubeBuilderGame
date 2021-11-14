/*********************************************************
** Project: Cube Builder Game
** File: WorldMapGenerator.h
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Generates predefined world maps
***********************************************************/

#ifndef WORLDMAPGENERATOR_H
#define WORLDMAPGENERATOR_H

#include "WorldMap.h"
#include "WoodlandSlab.h"
#include "GrassSlab.h"

namespace game {
    enum WORLD_MAP_SEED {
        BASIC_SMALL = 0,
        BASIC_MEDIUM = 1,
        BASIC_LARGE = 2
    };
}

class WorldMapGenerator {
private:
    WorldMapGenerator();
    static WorldMap* basic1Small();
    static WorldMap* basic1Medium();
    static WorldMap* basicLarge();
public:
    static WorldMap* generateWorld(game::WORLD_MAP_SEED seed);
};

#endif // WORLDMAPGENERATOR_H
