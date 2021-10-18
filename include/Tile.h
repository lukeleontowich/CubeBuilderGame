#ifndef TILE_H
#define TILE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Tile {
public:
    Tile();
    ~Tile();
    float vertices[4*8] = {
        0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int vbo, vao, ebo;
};

#endif // TILE_H
