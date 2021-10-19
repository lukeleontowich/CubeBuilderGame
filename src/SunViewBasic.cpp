/*****************************************************
** Project: Cube Builder Game
** File: SunViewBasic.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implements SunViewBasic.h
*****************************************************/

#include "SunViewBasic.h"

SunViewBasic::SunViewBasic(){}

SunViewBasic::~SunViewBasic(){}

void SunViewBasic::draw(Sun* sun) {
    //  Get a basic cube
    auto cube = GameResources::getCubeWithoutNormals();

    //  Get a simple shader
    auto shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", game::CUBE_SHADER_NO_NORMALS);

    glUseProgram(shader.id());
    glBindVertexArray(cube.vao);

    auto view = GameResources::getViewMatrix();
    auto projection = GameResources::getProjectionMatrix();
    auto model = glm::mat4(1.0f);

    //  Translate to the sun's position
    model = glm::translate(model, sun->getPos());

    //  Set Matrices
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(view));

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                       1, GL_FALSE, glm::value_ptr(model));

    //  Bind Texture
    GameResources::bind(game::WALL);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
