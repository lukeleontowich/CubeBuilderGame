#ifndef WOODLANDSLABVIEW1_H
#define WOODLANDSLABVIEW1_H

#include "GameResources.h"
#include "SlabViewBase1.h"

class WoodlandSlabView1 : public SlabViewBase1 {
public:
    WoodlandSlabView1();
    virtual ~WoodlandSlabView1();
    virtual void draw(int world_map_x, int world_map_z, Slab* slab);
    void drawTreeModels(int world_map, int world_map_z, Slab* slab);
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab);
};

#endif // WOODLANDSLABVIEW1_H
