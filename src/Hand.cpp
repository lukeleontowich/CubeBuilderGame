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
        //  Draw Cube to place
        auto model = glm::mat4(1.0f);
        auto shift_prime = glm::vec3(int(shift.x)+0.5, int(shift.y), int(shift.z)+0.5);
        model = glm::translate(model, shift_prime);
        auto shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", game::CUBE_SHADER_NO_NORMALS);
        auto cube = GameResources::getCubeWithoutNormals();
        shader.use();
        GameResources::bind(_current_texture);
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                            1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                            1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                            1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(cube.vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

bool Hand::block_in_hand() {
    return _block_in_hand;
}

game::TEXTURE_TYPE Hand::current_texture() {
    return _current_texture;
}
