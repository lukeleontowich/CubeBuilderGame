/**********************************************
** Project: Ultimate Mayor
** File: Camera.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Define the camera in a struct
**********************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//  Define the Camera struct
typedef struct {
    //  Position of the camera
    //  Initialize the original position
    glm::vec3 pos = glm::vec3(0.0f, 2.5f, 0.0f);

    //  Up vector
    //  Describes the up direction of the camera
    //  Initialize the up vector to upright
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    //  Direction vector
    //  Describes the direction that the camera is looking at
    //  Initialize the original position
    glm::vec3 dir = glm::vec3(0.0f, 0.0f, -1.0f);

    //  The yaw is the angle defined in the xz plane
    //  Otherwise stated it is the degree of which you are looking left or right
    float yaw = -90.0f;

    //  The pitch is the height that you are looking at
    float pitch = 0.0f;
} Camera;


#endif // CAMERA_H
