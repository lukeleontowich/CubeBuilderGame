#ifndef SKY_H
#define SKY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

/*****************************************************
** Project: Cube Builder Game
** File: Sky.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Describes the color of the sky
** The sky is essentially a giant box with 8 vertex colours
** Using OpenGL we can blend the colors of the 8 vertices
** to create the color of the sky
*****************************************************/

class Sky {
private:
    //  initialization
    void init();

    //  states
    bool sunrise_state = false;
    bool sunset_state = false;

    //  sunrise/ sunset colors
    glm::vec4 sunrise_color;
    glm::vec4 sunset_color;

    //  vertex colors
    float color1[4];
    float color2[4];
    float color3[4];
    float color4[4];
    float color5[4];  //  sunset color
    float color6[4];  //  sunset color
    float color7[4];  //  sunrise color
    float color8[4];  //  sunrise color

    //  8 vertices in 3D space
    float vertices [8*3] ={
        -0.5f,0.5f,-0.5f,
        -0.5f,0.5f,0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,

        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f
    };
    unsigned int indices[3*12] = {
        0,1,2,
        1,2,3,

        4,5,6,
        5,6,7,

        0,1,5,
        0,4,5,

        2,3,7,
        2,6,7,

        0,2,6,
        0,4,6,

        1,5,7,
        1,3,7
    };
    unsigned int _vao, _vbo, _ebo;

public:
    /** Constructor  **/
    Sky();

    /** Desctructor  **/
    ~Sky();

    /** update()
    ** @param const glm::vec4&
    ** @return void
    ** Description: updates the overall color of the sky
    ** The color parameter is a function of the state of the sun
    ** The color calculation is done outside this class (skyController.h)
    ** If we are in sunrise_state or sunset_state the color
    ** of the sunset/sunrise will blend into the overall color of the
    ** sky
    **/
    void update(const glm::vec4& color);

    /** enableSunrise()
    ** @param none
    ** @return void
    ** Description: Enables sunrise_state
    **/
    void enableSunrise();

    /** disableSunrise()
    ** @param none
    ** @return void
    ** Description: Disables sunrise_state
    **/
    void disableSunrise();

    /** enableSunset()
    ** @param none
    ** @return void
    ** Description: Enables sunset_state
    **/
    void enableSunset();

    /** disableSunset()
    ** @param none
    ** @return void
    ** Description: Disables sunset_state
    **/
    void disableSunset();

    /** setSunriseColor()
    ** @param const glm::vec4&
    ** @return void
    ** Description: Set the sunrise_color
    **/
    void setSunriseColor(const glm::vec4& color);

    /** setSunsetColor()
    ** @param const glm::vec4&
    ** @return void
    ** Description: Set the setset_color
    **/
    void setSunsetColor(const glm::vec4& color);

    /** destroy()
    ** @param none
    ** @return void
    ** Description: Deallocates the buffers and vertex arrays
    **/
    void destroy();

    /** vao()
    ** @param none
    ** @return unsigned int
    ** Description: Returns vao
    **/
    unsigned int vao() {return _vao;}
};

#endif // SKY_H
