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
    //  Shader needed to draw crosshairs
    game::Shader shader;

    //  vertex information
    float vertices[8] ={
        -0.05f, 0.0f,
        0.05f, 0.0f,
        0.0f, -0.05f,
        0.0f, 0.05f
    };
    unsigned vao, vbo;

public:
    /**  Constructor  **/
    CrossHairs();

    /**  Destructor  **/
    ~CrossHairs();

    /** draw()
    ** @param none
    ** @return none
    ** Description: Draws the crosshairs
    **/
    void draw();

    /** destroy()
    ** @param none
    ** @return none
    ** Description: Deallocates memory from vertex arrays and buffers
    **/
    void destroy();
};

#endif // CROSSHAIRS_H
