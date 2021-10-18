#include "SlabDecorator.h"

SlabDecorator::SlabDecorator(Slab* s) : slab(s) {
}

SlabDecorator::~SlabDecorator() {
    if (slab != nullptr) delete slab;
}

void SlabDecorator::draw(int world_map_x, int world_map_z,
                      game::Texture& texture, game::Shader& shader,
                      Tile& tile, Cube& cube) {

    slab->draw(world_map_x, world_map_z, texture, shader, tile, cube);
}
