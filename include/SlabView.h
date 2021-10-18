#ifndef SLABVIEW_H
#define SLABVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameResources.h"

class Slab;
#include "Slab.h"




class SlabView {
public:
    SlabView();
    virtual ~SlabView();
    virtual void draw(int world_map_x, int world_map_z, Slab* slab) = 0;
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab) = 0;
};

#endif // SLABVIEW_H
