
/*****************************************************
** Project: Cube Builder Game
** File: SlabViewBase1.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of SlabViewBase1.h
*****************************************************/

#include "SlabViewBase1.h"
#include "SkyController.h"

SlabViewBase1::SlabViewBase1() {}

SlabViewBase1::~SlabViewBase1() {}

constexpr float brightness_minimum = 0.25;

void SlabViewBase1::setBrightness(game::Shader& shader) {
    float temp_value = sin(glm::radians(GameResources::getLightAngle()));
    //  Make correction for a negative number
    if (temp_value < 0.0) {
        temp_value = 0.0;
    }
    float brightness = temp_value * (1.0 - brightness_minimum) + brightness_minimum ;

    glUniform1f(glGetUniformLocation(shader.id(), "brightness"), brightness);
}

void SlabViewBase1::drawTiles(int world_map_x, int world_map_z, Slab* slab) {
        //  Set up shader first
    auto shader = GameResources::loadShader("shaders/tile.vs",
                                            "shaders/tile.fs",
                                            game::TILE_SHADER_NORMALS);


    //  Tiles
    auto tile = GameResources::getTileWithNormals();

    //  Cubes
    auto cube = GameResources::getCubeWithNormals();

    //  use shader program
    shader.use();

    //  Bind vertex array
    glBindVertexArray(tile.vao);

    //  Set up matrices
    auto view = GameResources::getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(view));
    auto projection = GameResources::getProjectionMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));

    //  Set brightness
    this->setBrightness(shader);

    glUniform1i(glGetUniformLocation(shader.id(), "texture1"), 0);



    //  get tile map
    auto tilemap = slab->getLocalSlabMap();

    //  get current texture
    auto current_texture = tilemap[0];

    //  Bind the current texture
    GameResources::bind(current_texture);

    //  go through and draw all tiles
    for (unsigned int i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        //  check if we need to change texture
        if (tilemap[i] != current_texture) {
            current_texture = tilemap[i];
            GameResources::bind(current_texture);
        }
        //  load identity matrix
        auto model = glm::mat4(1.0f);

        //  shift to each (x, z) location
        auto shift = glm::vec3(world_map_x * SLAB_SIZE + i / SLAB_SIZE + 0.5,
                               slab->height() - 0.5,
                               world_map_z * SLAB_SIZE + i % SLAB_SIZE + 0.5);

        //  Set the view pos for lighting
        glUniform3fv(glGetUniformLocation(shader.id(), "viewPos"),
                     1, glm::value_ptr(shift));

        //  Do translation
        model = glm::translate(model, shift);

        //  update shader
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                           1, GL_FALSE, glm::value_ptr(model));

        //  Draw Tiles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void SlabViewBase1::drawCubes(int world_map_x, int world_map_z, Slab* slab) {
    //  Get shader
    auto shader = GameResources::loadShader("shaders/cube.vs", "shaders/cube.fs", game::CUBE_SHADER_NORMALS);

    //  Get cube info
    auto cube = GameResources::getCubeWithNormals();

    //  get cube map
    auto cube_map = slab->getCubeMapRef();

    //  Set a default current texture
    game::TEXTURE_TYPE current_texture = game::GRASS;


    //  Start setting lighting details
    shader.use();

    glUniform3fv(glGetUniformLocation(shader.id(), "material.color"),
                 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform1i(glGetUniformLocation(shader.id(), "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(shader.id(), "material.specular"), 0);
    glUniform1f(glGetUniformLocation(shader.id(), "material.shininess"), 64.0f);

    glUniform3fv(glGetUniformLocation(shader.id(), "light.position"),
                 1, glm::value_ptr(GameResources::getLightPos()));
    glUniform3fv(glGetUniformLocation(shader.id(), "light.ambient"),
                 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
    glUniform3fv(glGetUniformLocation(shader.id(), "light.diffuse"),
                 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    glUniform3fv(glGetUniformLocation(shader.id(), "light.specular"),
                 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform1f(glGetUniformLocation(shader.id(), "light.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.id(), "light.linear"), 0.000001f);
    glUniform1f(glGetUniformLocation(shader.id(), "light.quadratic"), 0.000001f);


    glUniform3fv(glGetUniformLocation(shader.id(), "viewPos"),
                 1, glm::value_ptr(GameResources::getPlayerPos()));

    //  Calculate brightness
    this->setBrightness(shader);


    //  Set matrices
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));

    //  Draw
    for (auto it = cube_map->begin(); it != cube_map->end(); ++it) {
        //  Check if we need to change textures
        if ((*it).type != current_texture) {
            current_texture = (*it).type;
            GameResources::bind(current_texture);
        }

        //  Load identity
        auto model = glm::mat4(1.0f);


        //  Get shift vector
        auto shift = glm::vec3(world_map_x * SLAB_SIZE + (*it).x +0.5,
                               (*it).y + slab->height(),
                               world_map_z * SLAB_SIZE + (*it).z + 0.5);

        //  Do translation
        model = glm::translate(model, shift);

        //  Set the model matrix in shader
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                           1, GL_FALSE, glm::value_ptr(model));

        //  Bind vertex array
        glBindVertexArray(cube.vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}
