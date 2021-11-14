/**********************************************************
** Project: Cube Builder Game
** File: Slab.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Slab is the terrain of the map. Slab.h is a
** base class that implements many functions used by different
** types of slabs. The map is made up of many different types
** of slabs. A slab is essentially a giant cube that stores
** the information about the ground material and the different
** objects placed in there. The size of a slab is determined
** by a const variable SLAB_SIZE which defines the width and
** length of the slab. Note that the base of each slab is
** square. The height of the slab is determined by a const
** variable SLAB_MAX_HEIGHT. If the slab dimensions are
** going to be changed they must be done by changing these
** two variables. The final dimensions of the slab will be
** due trail and error of what fits best for the game.
** Another note is that Slab class and its children classes
** are following the MVC design patter. This means that the
** way the slab is rendered is determined by the leaves of
** of the SlabView classes
***********************************************************/

#ifndef SLAB_H
#define SLAB_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Tile.h"
#include "Cube.h"
#include "GameResources.h"

//  Forward declaration
class SlabView;
#include "SlabView.h"

#include <vector>
#include <algorithm>
#include <utility>

//  Slab dimensions
//  Static so that the dimensions are known at compile time
static constexpr unsigned int SLAB_SIZE = 20;
static constexpr unsigned int SLAB_MAX_HEIGHT = 100;


/**  Define a struct that contains the info of the cube
** The info needed is the type of texture of the cube
**  and the position in which the cube was placed
** The position is an integer value since the collision map
**  in the slab will need to be updated using integers
**/
typedef struct {
    //  Texture of cube
    game::TEXTURE_TYPE type;

    //  Position of cube
    int x;
    int y;
    int z;
} CubeInfo;

//  Code that determines the success and errors of adding and removing cubes
enum SLAB_CODE {
    REMOVE_SUCCESS = 0,
    ADD_SUCCESS = 1,
    POSITION_NOT_VALID = 2,
    POSITION_ALREADY_TAKEN = 3,
    POSITION_EMPTY = 4,
    ELEMENT_NOT_FOUND = 5
};

/** SLAB CLASS  **/
class Slab {
protected:
    /** initCollisionMap()
    ** @param none
    ** @return void
    ** Description: initializes the collision map
    **/
    virtual void initCollisionMap();

    //  ground of slab
    int local_slab_map[SLAB_SIZE*SLAB_SIZE];

    //  Cubes of slab
    std::vector<CubeInfo> cube_map;

    //  Collision map
    bool collision_map[SLAB_SIZE][SLAB_MAX_HEIGHT][SLAB_SIZE];

    //  Height of slab
    unsigned int _height = 2;

    //  Slab view implements how to render the slab
    SlabView* view = nullptr;

public:
    //  Constructor
    Slab();

    //  Virtual destructor
    virtual ~Slab();

    /** draw()
    ** @param int world_map_x: the x coordinate of the world map (the offset in the x direction)
    **          int world_map_z: the z coordinate of the world map (the offset in the z direction)
    **          bool draw_scenery: if true draw the scenery defined in the slab view
    ** @return void
    ** Description: The SlabView leaves implement how to draw this function
    **/
    virtual void draw(int world_map_x, int world_map_z, bool draw_scenery = false);

    /** collision()
    ** @param int x, int y, int z: The coordinates to check
    ** @return bool: return true if there is a collision
    ** Description: Uses the 3 dimension bool collision_map to determine if true or false
    **/
    virtual bool collision(int x, int y, int z);

    /** addElement()
    ** @param TEXTURE_TYPE type: the type of texture to wrap the cube with
    **        vec3 pos: The position of the cube to be placed
    ** @return SLAB_CODE: see above for SLAB_CODE meanings
    ** Description: Add a cube to the slab with a given texture, if
    **              position is already taken then add nothing
    **/
    virtual SLAB_CODE addElement(game::TEXTURE_TYPE type, glm::vec3 pos);

    /** removeElement()
    ** @param vec3 pos: position of cube to be removed
    ** @return SLAB_CODE: see above for SLAB_CODE meanings
    ** Description: Removes a cube, if cube exists there
    **/
    virtual SLAB_CODE removeElement(glm::vec3 pos);

    /** checkPosIsValid()
    ** @param vec3 pos: position to check validility
    ** @return bool: return true if valid
    ** Description: Checks that a position is valid and not out of range since
    **              the collision map is a 3 dimensional array.
    **/
    virtual bool checkPosIsValid(glm::vec3 pos);

    /** height()
    ** @param none
    ** @return unsigned int: return the height
    ** Description: getter for the slab height
    **/
    virtual unsigned int height() {return _height;}

    /** getLocalSlabMap()
    ** @param none
    ** @return int*
    ** Description returns a reference to the local_slab_map
    **/
    virtual int* getLocalSlabMap() {return local_slab_map;}

    /** getCubeMapRef()
    ** @param none
    ** @return vector<CubeInfo>
    ** Description: returns a reference to the cube_map
    **/
    virtual std::vector<CubeInfo>* getCubeMapRef() {return &cube_map;}
};

#endif // SLAB_H
