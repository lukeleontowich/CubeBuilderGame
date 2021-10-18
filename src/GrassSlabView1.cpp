/*****************************************************
** Project: Ultimate Mayor
** File: GrassSlabView1.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: **
** Implements the GrassSlabView1 class
*****************************************************/

#include "GrassSlabView1.h"

/** Constructor  **/
GrassSlabView1::GrassSlabView1() {
    //  Random seed
    srand(time(NULL));

    //  Default grass density
    grass_density = 5;

    //  initialize the grass array
    initGrassArray();
}

/** Destructor  **/
GrassSlabView1::~GrassSlabView1() {}

/** draw() **/
void GrassSlabView1::draw(int world_map_x, int world_map_z, Slab* slab) {
    //  draw ground
    this->drawTiles(world_map_x, world_map_z, slab);

    //  draw cubes
    this->drawCubes(world_map_x, world_map_z, slab);
}

/**  DrawGrassModels()  **/
void GrassSlabView1::drawGrassModels(int world_map_x, int world_map_z, Slab* slab) {
    //  get shader
    auto shader = GameResources::loadShader("shaders/object.vs", "shaders/object.fs", game::OBJECT_SHADER1);
    shader.use();

    //  Set Shader contents
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));



    //  get grass model
    auto grass = GameResources::loadModel("objects/grass1/grass1.obj", game::MODEL_GRASS1);

    //  Shift to each (x, z) location
    for (unsigned int i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        //  check if we need to draw grass and that there is no cube in that position
        if (grass_array[i] != 0 && !slab->collision(i / SLAB_SIZE, 0, i % SLAB_SIZE)) {

            //  We want to draw 5 grass per tile
            for (int j = 0; j < 5; j ++) {
                //  identity matrix
                auto model = glm::mat4(1.0f);

                //  k1 and k2 are the location of the grass on the tile (k1, k2)
                float k1 = 0.0f;
                float k2 = 0.0f;
                switch (j) {
                    case 0: k1 = -0.25; k2 = 0.25; break;
                    case 1: k1 = 0.25; k2 = 0.25; break;
                    case 2: k1 = 0.0; k2 = 0.0; break;
                    case 3: k1 = -0.25; k2 = -0.25; break;
                    case 4: k1 = 0.25; k2 = -0.25; break;
                }
                auto shift = glm::vec3(world_map_x * SLAB_SIZE + i / SLAB_SIZE + k1,
                                   slab->height() - 0.5,
                                   world_map_z * SLAB_SIZE + i % SLAB_SIZE + k2);

                model = glm::translate(model, shift);

                glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                                   1, GL_FALSE, glm::value_ptr(model));

                grass.draw(shader);
            }
        }
    }
}

/**  drawScenery()  **/
void GrassSlabView1::drawScenery(int world_map_x, int world_map_z, Slab* slab) {
    this->drawGrassModels(world_map_x, world_map_z, slab);
}


/**  generateRandomNumber()  **/
unsigned int GrassSlabView1::generateRandomNumber() {
    return rand() % grass_density;
}


/**  initGrassArray  **/
void GrassSlabView1::initGrassArray() {
    for (unsigned int i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        grass_array[i] = this->generateRandomNumber();
    }
}
