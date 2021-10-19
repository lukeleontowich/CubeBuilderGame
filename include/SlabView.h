/*****************************************************
** Project: Cube Builder Game
** File: SlabView.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Base class. SlabView implements methods
** of drawing a Slab
*****************************************************/

#ifndef SLABVIEW_H
#define SLABVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameResources.h"

//  forward declaration
class Slab;
#include "Slab.h"

class SlabView {
public:
    /** Constructor  **/
    SlabView();

    /**  Desctructor  **/
    virtual ~SlabView();

    /** draw()
    ** @param int, int, Slab*
    ** @return none
    ** Description: Draws the slab, implemented in concrete classes
    **/
    virtual void draw(int world_map_x, int world_map_z, Slab* slab) = 0;

    /** drawScenery()
    ** @param int, int, Slab*
    ** @return none
    ** Description: Draws the 3D objects (aside from the cubes). Implemented
    ** in concrete classes
    **/
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab) = 0;
};

#endif // SLABVIEW_H
