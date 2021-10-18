#ifndef SLABVIEWBASE1_H
#define SLABVIEWBASE1_H

#include <SlabView.h>


class SlabViewBase1 : public SlabView {
public:
    SlabViewBase1();
    virtual ~SlabViewBase1();

    virtual void draw(int world_map_x, int world_map_z, Slab* slab) = 0;

    virtual void drawTiles(int world_map_x, int world_map_z, Slab* slab);
    virtual void drawCubes(int world_map_x, int world_map_z, Slab* slab);
    virtual void setBrightness(game::Shader& shader);
};

#endif // SLABVIEWBASE1_H
