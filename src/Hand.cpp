/*****************************************************
** Project: Cube Builder Game
** File: Hand.cpp
** Author: Luke Leontowich
** Date: Novemeber 12, 2021
** Description: Implements Hand.h
*****************************************************/

#include "Hand.h"

Hand::Hand() {
    _current_texture = game::ROCK;
    _block_in_hand = true;
}

Hand::~Hand() {}

void Hand::changeTexture(game::TEXTURE_TYPE texture) {
    _current_texture = texture;
}

void Hand::changeBlockInHand(bool state) {
    _block_in_hand = state;
}

void Hand::draw(const glm::vec3& shift) {
    if (_block_in_hand) {
        //  load identity matrix
        auto model = glm::mat4(1.0f);

        //  offset for the shift
        auto shift_prime = glm::vec3(int(shift.x)+0.5, int(shift.y), int(shift.z)+0.5);

        //  translate to shift
        model = glm::translate(model, shift_prime);

        //  load shader
        auto shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", game::CUBE_SHADER_NO_NORMALS);

        //  get geometric cube information
        auto cube = GameResources::getCubeWithoutNormals();

        //  use shader
        shader.use();

        //  Bind texture
        GameResources::bind(_current_texture);

        //  Set MVP matrices
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                            1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                            1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                            1, GL_FALSE, glm::value_ptr(model));

        //  Bind vertex arrays
        glBindVertexArray(cube.vao);

        //  draw
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

bool Hand::block_in_hand() {
    return _block_in_hand;
}

game::TEXTURE_TYPE Hand::current_texture() {
    return _current_texture;
}
