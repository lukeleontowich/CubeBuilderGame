#include "SunViewBasic.h"

SunViewBasic::SunViewBasic(){}

SunViewBasic::~SunViewBasic(){}

void SunViewBasic::draw(Sun* sun) {
    auto cube = GameResources::getCubeWithoutNormals();
    auto shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", game::CUBE_SHADER_NO_NORMALS);

    glUseProgram(shader.id());
    glBindVertexArray(cube.vao);

    auto view = GameResources::getViewMatrix();
    auto projection = GameResources::getProjectionMatrix();
    auto model = glm::mat4(1.0f);

    model = glm::translate(model, sun->getPos());

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(view));

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(projection));

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                       1, GL_FALSE, glm::value_ptr(model));
    GameResources::bind(game::WALL);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
