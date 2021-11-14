/*****************************************************
** Project: Cube Builder Game
** File: main.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Main file for game
*****************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "Shader.h"
#include "Texture.h"
#include "Tile.h"
#include "Cube.h"
#include "Slab.h"
#include "GrassSlab.h"
#include "WorldMap.h"
#include "WaterSlab.h"
#include "DesertSlab.h"
#include "Camera.h"
#include "Model.h"
#include "GameResources.h"
#include "Sky.h"
#include "Sun.h"
#include "SunViewBasic.h"
#include "SkyController.h"
#include "WoodlandSlab.h"
#include "CrossHairs.h"
#include "Hand.h"
#include "CubeBuilderGame.h"

//  Callback Functions
void reshape(GLFWwindow* window, int width, int height);
void mouse(GLFWwindow* window, double xpos, double ypos);

//  Timer
float delta_time = 0.0f;
float last_frame = 0.0f;

//  Game
CubeBuilderGame* cubegame = nullptr;

/*************************************************************
***   MAIN   *************************************************
*************************************************************/
int main() {
    /***   Initializing ***/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //  Create Window
    auto window = glfwCreateWindow(GameResources::WIDTH, GameResources::HEIGHT, "Cube Builder Game", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error creating window\n";
        glfwTerminate();
        return 1;
    }


    glfwMakeContextCurrent(window);

    //  Set callbacks
    glfwSetFramebufferSizeCallback(window, reshape);
    glfwSetCursorPosCallback(window, mouse);

    //  Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //  Enable depth testing
    glEnable(GL_DEPTH_TEST);

    //  Initialize cube game
    cubegame = new CubeBuilderGame(game::BASIC_MEDIUM);


    //  Disable mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    /*********** MAIN LOOP  ***********************/
    while (!glfwWindowShouldClose(window)) {

        //  Set background color
        glClearColor(0.0, 1.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        //  Set Projection Matrix
        GameResources::setProjectionMatrix(glm::perspective(glm::radians(45.0f),
                                                            float(GameResources::WIDTH) / float(GameResources::HEIGHT),
                                                            0.1f, VIEW_DISTANCE));
        //  Update Game
        cubegame->update(delta_time);

        //  Draw Game
        cubegame->draw();

        //  Swap buffers and poll events
        glfwSwapBuffers(window);
        //  Process input
        //input(window);
        cubegame->input(window);
        glfwPollEvents();
    }

    //  Clean up resources
    GameResources::destroy();
    cubegame->destroy();
    delete cubegame;

    glfwTerminate();
    return 0;
}

/***************************************************************
***   RESHAPE   ************************************************
***************************************************************/
void reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    GameResources::WIDTH = width;
    GameResources::HEIGHT = height;
}


/******************************************************************
***   MOUSE   *****************************************************
******************************************************************/
void mouse(GLFWwindow* window, double xpos, double ypos) {
    cubegame->mouse(window, xpos, ypos);
}

