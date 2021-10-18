#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>

#include "Slab.h"
#include "GrassSlab.h"
#include "WaterSlab.h"
#include "Camera.h"

enum MODE {
    ADD = 1,
    REMOVE = 0
};

class WorldMap {
public:
    //  All maps are squares
    //  map_size = map_size_length * map_size_length
    explicit WorldMap(const unsigned& map_side_length);
    ~WorldMap();

    //  No extra slabs can be added once vector is full
    int addSlab(Slab* slab);

    //  Any left over slab spaces will be filled with water slabs
    int draw(glm::vec3 pos);

    //  Check that the map is square
    bool mapIsSquare();

    //  Get the index of a given (x, z) coordinate
    //  Note that the map is single dimension array storing 2 dimensions
    //  Return -1 if slabIndex is out of range
    int getSlabIndex(int world_map_x, int world_map_z);

    //  Fills the remaining spaces in the map
    void fillRestOfMap();

    //  Checks if map is full
    bool mapIsFull();

    //  Collision
    bool collision(glm::vec3 pos);

    //  Add Cube
    bool addCube(game::TEXTURE_TYPE type, glm::vec3 ply_pos, glm::vec3 ptr_pos);

    //  Remove Cube
    bool removeCube(glm::vec3 pos);

    //  Convert world_map coordinates to local slab coordinates
    void convertToLocalSlabCoordintates(glm::vec3 pos,
                                        float& local_slab_x, float& local_slab_z);

    //  Get the block that the mouse pointer is looking at
    glm::vec3 getMousePointerLocation(const Camera& camera, MODE mode);

    //  Use for testing
    std::vector<Slab*>* getWorldMap() {return &world_map;}

private:
    unsigned map_size;
    std::vector<Slab*> world_map;
    unsigned slabs_added = 0;
};

#endif // WORLDMAP_H
