#include "Slab.h"
/**********************************************************
** Project: Ultimate Mayor
** File: Slab.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of Slab.h
***********************************************************/

/** Constructor  **/
Slab::Slab() {}

/** Desctructor **/
Slab::~Slab() {
    if (view != nullptr) {
        delete view;
        view = nullptr;
    }
}

/** draw **/
void Slab::draw(int world_map_x, int world_map_z, bool draw_scenery) {
    //  Draw the slab
    view->draw(world_map_x, world_map_z, this);

    //  draw the scenery if desired
    if (draw_scenery) {
        view->drawScenery(world_map_x, world_map_z, this);
    }
}

/**  collision **/
bool Slab::collision(int x, int y, int z) {
    //  Cases outside the slab
    if (x < 0 || x >= int(SLAB_SIZE) ||
        z < 0 || z >= int(SLAB_SIZE)) return false;

    //  Case that you go too high or too low
    if (y >= int(SLAB_MAX_HEIGHT) || y < 0) return true;

    //  return the value at the given position
    return collision_map[x][y][z];
}

/**  addElement  **/
SLAB_CODE Slab::addElement(game::TEXTURE_TYPE type, glm::vec3 pos) {
    //  Check if position is valid
    if (!this->checkPosIsValid(pos)) {
        return POSITION_NOT_VALID;
    }
    //  convert all positions to integers
    int x = int(pos.x);
    int y = int(pos.y);
    int z = int(pos.z);

    //  check that the position isnt already taken
    if (collision_map[x][y][z]) return POSITION_ALREADY_TAKEN;

    //  Push new cube into vector
    CubeInfo cube;
    cube.type = type;
    cube.x = x;
    cube.y = y;
    cube.z = z;
    cube_map.push_back(cube);

    //  Update the collision map
    collision_map[x][y][z] = true;

    //  The y blocks take up 2, due to the height of player
    if (y - 1 >= 0) {
        //collision_map[x][y-1][z] = true;
    }
    return ADD_SUCCESS;
}

/** removeElement  **/
SLAB_CODE Slab::removeElement(glm::vec3 pos) {
    //  Check if position is valid
    if (!checkPosIsValid(pos)) {
        return POSITION_NOT_VALID;
    }
    //  Convert to integers
    int x = int(pos.x);
    int y = int(pos.y);
    int z = int(pos.z);

    //  Check if the element to be removed exists
    if (!collision_map[x][y][z]) {
        return POSITION_EMPTY;
    }

    //  Find the element
    auto it = std::find_if(cube_map.begin(), cube_map.end(),
                           [&x, &y, &z](const CubeInfo& c1)->bool{
                                if (c1.x == x && c1.y == y && c1.z == z) return true;
                                else return false;
                           });
    if (it != cube_map.end()) {
        cube_map.erase(it);
        collision_map[x][y][z] = false;
        return REMOVE_SUCCESS;
    } else {
        return ELEMENT_NOT_FOUND;
    }
}

/** checkPosIsValid  **/
bool Slab::checkPosIsValid(glm::vec3 pos) {
    pos.x = int(pos.x);
    pos.y = int(pos.y);
    pos.z = int(pos.z);

    if (pos.x < 0 || pos.x >= SLAB_SIZE ||
        pos.y < 0 || pos.y >= SLAB_MAX_HEIGHT ||
        pos.z < 0 || pos.z >= SLAB_SIZE) return false;

    else return true;
}

/** Private function: initCollisionMap  **/
void Slab::initCollisionMap() {
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        for (unsigned j = 0; j < SLAB_MAX_HEIGHT; ++j) {
            for (unsigned k = 0; k < SLAB_SIZE; ++k) {
                collision_map[i][j][k] = false;
            }
        }
    }
}
