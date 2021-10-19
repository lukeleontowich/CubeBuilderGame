/*****************************************************
** Project: Cube Builder Game
** File: WorldMap.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Stores all the game slabs, which store all
** the game information. Designates what to draw in each slab
** or whether or not to draw a slab, depending on player position
*****************************************************/
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

//  MODE is needed for Adding and Removing Cubes
enum MODE {
    ADD = 1,
    REMOVE = 0
};

class WorldMap {
private:
    //  Size of map
    unsigned map_size;

    //  Store the slabs
    std::vector<Slab*> world_map;

    //  Number of slabs added to the map
    //  insurance
    unsigned slabs_added = 0;

public:
    /** Constructor
    ** All maps are squares
    **  map_size = map_size_length * map_size_length
    **/
    explicit WorldMap(const unsigned& map_side_length);

    /** Desctructor  **/
    ~WorldMap();

    /** addSlab()
    ** @param Slab*
    ** @return int
    ** Description: Adds a slab to the world_map
    ** No extra slabs can be added once vector is full
    **/
    int addSlab(Slab* slab);

    /**  draw()
    ** @param glm::vec3
    ** @return int
    ** Description: Designates what slabs will be drawn and in how much
    ** detail the slabs should be drawn
    ** If slab isn't full, draw will fill the world_map before drawing
    **/
    int draw(glm::vec3 pos);

    /** mapIsSquare()
    ** @param none
    ** @return bool
    ** Description: Checks if the map is square. Since the world_map is
    ** a single dimension array storing a 2D world, we need to make
    ** sure that the number of elements are a perfect square
    **/
    bool mapIsSquare();

    /** getSlabIndex()
    ** @param int, int
    ** @return int
    ** Description: Get the index of a given (x, z) coordinate
    ** Note that the map is single dimension array storing 2 dimensions
    ** Return -1 if slabIndex is out of range
    **/
    int getSlabIndex(int world_map_x, int world_map_z);

    /** fillRestOfMap()
    ** @param none
    ** @return void
    ** Description: Fills the remaining spaces in the map
    **/
    void fillRestOfMap();

    /** mapIsFull()
    ** @param none
    ** @return bool
    ** Description:  Checks if map is full
    **/
    bool mapIsFull();

    /** collision()
    ** @param glm::vec3
    ** @return boo
    ** Description: Check if the player is colliding with a cube or object or ground
    **/
    bool collision(glm::vec3 pos);

    /** addCube()
    ** @param gam::TEXTURE_TYPE, glm::vec3, glm::vec3
    ** @return bool
    ** Description: The ptr_pos defines the cube location of where the player
    ** is looking. If this is a valid location, add a cube to the slab that the ptr
    ** is pointing at
    **/
    bool addCube(game::TEXTURE_TYPE type, glm::vec3 ply_pos, glm::vec3 ptr_pos);

    /** removceCube()
    ** @param glm::vec3
    ** @return bool
    ** Description: The pos is where the player's crosshairs are looking at. If looking
    ** at a cube, then remove it
    **/
    bool removeCube(glm::vec3 pos);

    /** convertToLocalSlabCoordinates()
    ** @param glm::vec3, float&, float&
    ** @return void
    ** Description: Convert world_map coordinates to local slab coordinates
    **/
    void convertToLocalSlabCoordintates(glm::vec3 pos,
                                        float& local_slab_x, float& local_slab_z);

    /**  getMousePointerLocation()
    ** @param const Camera&, MODE mode
    ** @return glm::vec3
    ** Description: Get the block that the mouse pointer is looking at
    **/
    glm::vec3 getMousePointerLocation(const Camera& camera, MODE mode);

    //  Used for testing
    std::vector<Slab*>* getWorldMap() {return &world_map;}
};

#endif // WORLDMAP_H
