#ifndef SKY_H
#define SKY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"



class Sky {
public:
    Sky();
    ~Sky();
    void update(const glm::vec4& color);
    void enableSunrise();
    void disableSunrise();
    void enableSunset();
    void disableSunset();
    void setSunriseColor(const glm::vec4& color);
    void setSunsetColor(const glm::vec4& color);
    void destroy();

    //  getters
    unsigned int vao() {return _vao;}

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
    float color1[4];  //
    float color2[4];  //
    float color3[4];
    float color4[4];
    float color5[4];  //  sunset color
    float color6[4];  //  sunset color
    float color7[4];  //  sunrise color
    float color8[4];  //  sunrise color


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
};

#endif // SKY_H
