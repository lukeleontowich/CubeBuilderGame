/*****************************************************
** Project: Cube Builder Game
** File: SunView.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Base class for drawing sun. Allows for
** easy changing of drawing the sun.
*****************************************************/

#ifndef SUNVIEW_H
#define SUNVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//  Forward declaration
#include "Sun.h"
class Sun;

class SunView {
public:
    /**  Constructor  **/
    SunView();

    /** Destructor  **/
    virtual ~SunView();

    /** draw()
    ** @param Sun*
    ** @return void
    ** Description: Concrete classes implement drawing method
    **/
    virtual void draw(Sun* sun) = 0;
};

#endif // SUNVIEW_H
