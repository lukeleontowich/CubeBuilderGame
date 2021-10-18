#ifndef SLABDECORATOR_H
#define SLABDECORATOR_H

#include "Slab.h"


class SlabDecorator : public Slab {
public:
    SlabDecorator(Slab* s);
    virtual ~SlabDecorator();
    virtual void draw(int world_map_x, int world_map_z,
                      game::Texture& texure, game::Shader& shader,
                      Tile& tile, Cube& cube);
    virtual bool collision(glm::vec3 pos) = 0;
    virtual Slab* getSlabPtr() {return slab;}
private:
    Slab* slab = nullptr;
};

#endif // SLABDECORATOR_H
