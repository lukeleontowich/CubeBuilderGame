#include "WoodlandSlabView1.h"

WoodlandSlabView1::WoodlandSlabView1() {}

WoodlandSlabView1::~WoodlandSlabView1() {}

void WoodlandSlabView1::draw(int world_map_x, int world_map_z, Slab* slab) {
    this->drawTiles(world_map_x, world_map_z, slab);
    this->drawCubes(world_map_x, world_map_z, slab);
}

void WoodlandSlabView1::drawScenery(int world_map_x, int world_map_z, Slab* slab) {
    this->drawTreeModels(world_map_x, world_map_z, slab);
}

void WoodlandSlabView1::drawTreeModels(int world_map_x, int world_map_z, Slab* slab) {
    //  get shader
    auto shader = GameResources::loadShader("shaders/objects.vs", "shaders/objects.fs", game::OBJECT_SHADER1);

    shader.use();

    //  Set Shader contents
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));

    //  Get tree model
    auto tree = GameResources::loadModel("objects/tree1/tree1.obj", game::MODEL_TREE1);


    auto model = glm::mat4(1.0f);
    glm::vec3 shift = glm::vec3(world_map_x*SLAB_SIZE + SLAB_SIZE / 10,
                                slab->height() -0.5,
                                world_map_z*SLAB_SIZE + SLAB_SIZE / 5);
    model = glm::translate(model, shift);
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                       1, GL_FALSE, glm::value_ptr(model));
    tree.draw(shader);

    model = glm::mat4(1.0f);
    shift = glm::vec3(world_map_x*SLAB_SIZE + SLAB_SIZE / 2,
                      slab->height(),
                      world_map_z*SLAB_SIZE + SLAB_SIZE / 3);
    model = glm::translate(model, shift);
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                       1, GL_FALSE, glm::value_ptr(model));
    tree.draw(shader);
}
