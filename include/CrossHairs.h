/*****************************************************
** Project: Cube Builder Game
** File: CrossHairs.h
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Data needed to draw crosshairs
*****************************************************/

#ifndef CROSSHAIRS_H
#define CROSSHAIRS_H

#include "Shader.h"

class CrossHairs {
private:
    game::Shader shader;
    float vertices[8] ={
        -0.05f, 0.0f,
        0.05f, 0.0f,
        0.0f, -0.05f,
        0.0f, 0.05f
    };
    unsigned vao, vbo;
public:
    CrossHairs();
    virtual ~CrossHairs();
    void draw();
    void destroy();
};

#endif // CROSSHAIRS_H
