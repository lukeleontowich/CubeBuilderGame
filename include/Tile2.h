#ifndef TILE2_H
#define TILE2_H


class Tile2 {
public:
    Tile2();
    ~Tile2();
    //  Set up for tiles
    float vertices[5 * 4] = {
        0.5f,  0.0f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f
    };
    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int vao, vbo, ebo;
};

#endif // TILE2_H
