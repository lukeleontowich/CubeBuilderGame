/*****************************************************
** Project: Cube Builder Game
** File: TempSlabView.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implements TempSlabView.h
*****************************************************/

#include "TempSlabView.h"

TempSlabView::TempSlabView() {}

TempSlabView::~TempSlabView() {}

void TempSlabView::draw(int world_map_x, int world_map_z, Slab* slab) {

    //  Draw ground
    //  need to bind the tile vertex array
    glBindVertexArray(GameResources::getTile2().vao);

    //  Need to get correct shader
    auto shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", "basic_shader");

    glUseProgram(shader.id());

    //  set view and projection matrix in the shader
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));



    //  Get slab type
    auto ground_map = slab->getLocalSlabMap();

    //  bind the first texture
    auto current_texture = ground_map[0];
    GameResources::bind(current_texture);

    //  draw all tiles
    for (unsigned int i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        //  check if we need to change textures
        if (ground_map[i] != current_texture) {
            current_texture = ground_map[i];
            GameResources::bind(current_texture);
        }

        //  Load Identity
        auto model = glm::mat4(1.0f);

        //  shift to each (x, z) location
        auto shift = glm::vec3(world_map_x * SLAB_SIZE + i / SLAB_SIZE + 0.5,
                               slab->height() - 0.5,
                               world_map_z * SLAB_SIZE + i % SLAB_SIZE + 0.5);

        //  Do translation
        model = glm::translate(model, shift);

        //  update shader
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                           1, GL_FALSE, glm::value_ptr(model));

        //  Lets draw now
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void TempSlabView::drawScenery(int world_map_x, int world_map_z, Slab* slab) {

}
