#include "WorldMap.h"

WorldMap::WorldMap(const unsigned& map_side_length) {
    map_size = map_side_length * map_side_length;
    world_map.reserve(map_size);
}

WorldMap::~WorldMap() {
    for (auto it = world_map.begin(); it != world_map.end(); ++it) {
        delete *it;
    }
}

int WorldMap::addSlab(Slab* slab) {
    if (world_map.size() < map_size) {
        world_map.push_back(slab);
        return 1;
    } else {
        delete slab;
        return 0;
    }
}


bool WorldMap::mapIsSquare() {
    float sqrtf = sqrt(world_map.size());
    int sqrti = sqrt(world_map.size());

    if (abs(sqrtf - sqrti) < 0.000000001) {
        return true;
    } else {
        return false;
    }
}

//  Return -1 if index is bad
int WorldMap::getSlabIndex(int world_map_x, int world_map_z) {
    if (world_map_x < 0) return -1;
    if (world_map_z < 0) return -1;
    if (!this->mapIsSquare()) return -1;
    if (world_map_x >= sqrt(map_size)) return -1;
    if (world_map_z >= sqrt(map_size)) return -1;

    //  Calculate index
    int index = world_map_x * sqrt(map_size) + world_map_z;

    //  Check that this index is not too high
    if (index >= int(world_map.size())) return -1;

    return index;
}

void WorldMap::fillRestOfMap() {
    //  Fill the rest with grass
    int iterations = map_size - world_map.size();
    for (int i = 0; i < iterations; ++i) {
        world_map.push_back(new GrassSlab);
    }
}

bool WorldMap::mapIsFull() {
    if (map_size == world_map.size()) return true;
    else return false;
}

bool WorldMap::collision(glm::vec3 pos) {
    //  Check outerbounds first
    if (pos.x < 0.0 || pos.x >= SLAB_SIZE*sqrt(map_size) ||
        pos.y < 0.0 || pos.y >= SLAB_MAX_HEIGHT*sqrt(map_size) ||
        pos.z < 0.0 || pos.z >= SLAB_SIZE*sqrt(map_size))
        return true;

    //  Get location of local slab
    int world_map_x = int(pos.x) / SLAB_SIZE;
    int world_map_z = int(pos.z) / SLAB_SIZE;
    auto index = getSlabIndex(world_map_x, world_map_z);

    //  Index out of range so say there is a collision
    if (index == -1) return true;

    //  Convert to the local slab coordinates
    float local_x, local_y, local_z;

    local_y = pos.y - world_map[index]->height();

    //  If y < 0 then it is automatically too low
    if (local_y < 0.0) return true;


    //  Need to make a slight offset so that we don't see inside objects
    float off = 0.25;
    //  Check case 1
    convertToLocalSlabCoordintates(glm::vec3(pos.x - off, pos.y, pos.z - off),
                                   local_x, local_z);
    if (world_map[index]->collision(int(local_x), int(local_y), int(local_z)))
        return true;

    //  Check case 2
    convertToLocalSlabCoordintates(glm::vec3(pos.x - off, pos.y, pos.z + off),
                                   local_x, local_z);
    if (world_map[index]->collision(int(local_x), int(local_y), int(local_z)))
        return true;

    //  Check case 3
    convertToLocalSlabCoordintates(glm::vec3(pos.x + off, pos.y, pos.z + off),
                                   local_x, local_z);
    if (world_map[index]->collision(int(local_x), int(local_y), int(local_z)))
        return true;

    //  Check case 4
    convertToLocalSlabCoordintates(glm::vec3(pos.x + off, pos.y, pos.z + off),
                                   local_x, local_z);
    if (world_map[index]->collision(int(local_x), int(local_y), int(local_z)))
        return true;

    return false;
}

bool WorldMap::addCube(game::TEXTURE_TYPE type, glm::vec3 ply_pos, glm::vec3 ptr_pos) {
    if (int(ply_pos.x) == int(ptr_pos.x) &&
        int(ply_pos.y) == int(ptr_pos.y) &&
        int(ply_pos.z) == int(ptr_pos.z))
            return false;

    //  convert to world_map location
    int world_map_x = int(ptr_pos.x) / SLAB_SIZE;
    int world_map_z = int(ptr_pos.z) / SLAB_SIZE;


    //  get slab index
    auto index = getSlabIndex(world_map_x, world_map_z);

    //  Check for errors
    if (index == -1) return false;

    //  Get current slab
    auto current_slab = world_map[index];

    //  Get local slab coordinates
    float local_x, local_y, local_z;
    convertToLocalSlabCoordintates(ptr_pos, local_x, local_z);
    local_y = ptr_pos.y - current_slab->height();

    //  Add the cube
    if(current_slab->addElement(type, glm::vec3(local_x, local_y, local_z)) == ADD_SUCCESS) {
        return true;
    }


    return false;
}

bool WorldMap::removeCube(glm::vec3 pos) {
//  convert to world_map location
    int world_map_x = int(pos.x) / SLAB_SIZE;
    int world_map_z = int(pos.z) / SLAB_SIZE;


    //  get slab index
    auto index = getSlabIndex(world_map_x, world_map_z);

    //  Check for errors
    if (index == -1) return false;

    //  Get current slab
    auto current_slab = world_map[index];

    //  Get local slab coordinates
    float local_x, local_y, local_z;
    convertToLocalSlabCoordintates(pos, local_x, local_z);
    local_y = pos.y - current_slab->height();

    //  Add the cube
    if(current_slab->removeElement(glm::vec3(local_x, local_y, local_z)) == REMOVE_SUCCESS) {
        return true;
    }


    return false;
}

void WorldMap::convertToLocalSlabCoordintates(glm::vec3 pos,
                                              float& local_slab_x, float& local_slab_z) {
    //            /  DECIMAL PLACES /
    local_slab_x = pos.x - int(pos.x) + int(pos.x) % SLAB_SIZE;
    local_slab_z = pos.z - int(pos.z) + int(pos.z) % SLAB_SIZE;
}

//  ** Note that the function will return (-1, -1, -1) if the location is out of scope
glm::vec3 WorldMap::getMousePointerLocation(const Camera& camera, MODE mode) {

    //  First we need to get the point on the ground that the mouse is looking at
    //  To do this lets get the current slab that we are in
    //  convert to world_map location
    int world_map_x = int(camera.pos.x) / SLAB_SIZE;
    int world_map_z = int(camera.pos.z) / SLAB_SIZE;

        //  get slab index
    auto index = getSlabIndex(world_map_x, world_map_z);

    //  Check for bad input
    if (index < -1) return glm::vec3(-1.0, -1.0, -1.0);

    auto current_slab = world_map[index];



    //  We will need two points p1 and p2 to form the equation of a line
    //  p1 is given by camera.pos
    //  p2 will be (x2, 0, y2) since we are looking at the bottom of the map
    glm::vec3 p1 = camera.pos;
    glm::vec3 p2;


    //  We need to check if we are looking up or down
    //  The y2 location will either be the ground or the SLAB_MAX_HEIGHT
    float y;
    if (camera.pitch < 0) y = current_slab->height();
    else y = SLAB_MAX_HEIGHT;



    //  Lets get the length of vector that will go from (x1, y1, z1) to (x2, y2, z2)
    //  Form a right triangle from (x1, camera.pos.y, x1) to (x2, y, z2)
    //  We have the angle (pitch) and the length of adj side (camera.pos y - y) we want to find the length of opp side
    //  tan(theta) = opp / adj ==>> opp = tan(theta) * adj
    float length = abs((camera.pos.y - y) / tan(glm::radians(camera.pitch)));
    /*
    std::cout << "tan(pitch): " << tan(glm::radians(camera.pitch)) << "\n";
    std::cout << "length: " << length << "\n";
    */


    //  We are now have the length of the vector that sits on the xz plane
    //  The direction is simply given by camera.yaw
    //  To calculate x2
    p2.x = p1.x + cos(glm::radians(camera.yaw)) * length;
    //  To calculate z2
    p2.z = p1.z + sin(glm::radians(camera.yaw)) * length;
    //  As stated about y2 will be ground of the slab
    p2.y = y;
/*
    std::cout << "p2.x: " << int(p2.x) << "\n";
    std::cout << "p2.y: " << int(p2.y) << "\n";
    std::cout << "p2.z: " << int(p2.z) << "\n\n";
*/
    //  Now we need a parametrized equation of line
    //  Define a vector v such that V = p2 - p1
    glm::vec3 V = p2 - p1;

    //  Thus our equation of a line becomes:
    //  r(t) = p1 + t * V

    //  Now we need to find where the line intersects with a block or the ground

    glm::vec3 previous_vec = p1;
    float t = 0.0;
    while (t < 1.0){
        glm::vec3 temp = p1 + (t * V);

        //  check if there is a collision here
        //  Need to localize coordinates
        float local_x, local_y, local_z;
        convertToLocalSlabCoordintates(temp, local_x, local_z);
        local_y = temp.y - current_slab->height();
        if (current_slab->collision(int(local_x-0.5), int(local_y), int(local_z-0.5))) {

            /*
            std::cout << "collision\n";
            std::cout << "collision.x: " << int(temp.x) << "\n";
            std::cout << "collision.y: " << int(temp.y) << "\n";
            std::cout << "collision.z: " << int(temp.z) << "\n";
            */
            //  For add, we want to return the previous vector since this one is obiviously occupied
            if (mode == ADD)
                return previous_vec;
            //  For remove return current vector
            if (mode == REMOVE)
                return temp;
        }
        previous_vec = temp;

        t += 0.01;

        //  make a case if the positions are too far away
        if ((p1.x-temp.x)*(p1.x-temp.x) +
            (p1.y-temp.y)*(p1.y-temp.y) +
            (p1.z-temp.z)*(p1.z-temp.z)
            >= 4*4) {
            //  Return an impossible vector
            return glm::vec3(-1.0, -1.0, -1.0);
        }
    }

    //  Mouse is pointing at ground
    return previous_vec;

}


/**  DRAW  **/
int WorldMap::draw(glm::vec3 pos) {
    if (!this->mapIsFull()) {
        this->fillRestOfMap();
    }

    //  The map only draws 9 slabs at time
    //  Mainly to save processing power
    int world_map_x = int(pos.x) / SLAB_SIZE;
    int world_map_z = int(pos.z) / SLAB_SIZE;

    //  Draw Top left
    auto index = this->getSlabIndex(world_map_x - 1, world_map_z - 1);
    if (index != -1) {
        world_map[index]->draw(world_map_x - 1, world_map_z - 1, 1);
    }

    //  Draw Top center
    index = this->getSlabIndex(world_map_x, world_map_z - 1);
    if (index != -1) {
        world_map[index]->draw(world_map_x, world_map_z - 1);
    }

    //  Draw Top right
    index = this->getSlabIndex(world_map_x + 1, world_map_z - 1);
    if (index != -1) {
        world_map[index]->draw(world_map_x + 1, world_map_z - 1);
    }

    //  Draw Middle Left
    index = this->getSlabIndex(world_map_x - 1, world_map_z);
    if (index != -1) {
        world_map[index]->draw(world_map_x - 1, world_map_z);
    }

    /**  Draw Middle Center  **/
    index = this->getSlabIndex(world_map_x, world_map_z);
    if (index != -1) {
        world_map[index]->draw(world_map_x, world_map_z, false);
    }

    //  Draw Middle Right
    index = this->getSlabIndex(world_map_x + 1, world_map_z);
    if (index != -1) {
        world_map[index]->draw(world_map_x + 1, world_map_z);
    }

    //  Draw Bottom left
    index = this->getSlabIndex(world_map_x - 1, world_map_z + 1);
    if (index != -1) {
        world_map[index]->draw(world_map_x - 1, world_map_z + 1);
    }

    //  Draw Bottom center
    index = this->getSlabIndex(world_map_x, world_map_z + 1);
    if (index != -1) {
        world_map[index]->draw(world_map_x, world_map_z + 1);
    }

    //  Draw bottom right
    index = this->getSlabIndex(world_map_x + 1, world_map_z + 1);
    if (index != -1) {
        world_map[index]->draw(world_map_x + 1, world_map_z + 1);
    }

    return 1;
}
