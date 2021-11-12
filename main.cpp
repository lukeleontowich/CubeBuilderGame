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
#include "CitySlabDecorator.h"
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

Camera camera;


//  States
bool paused = false;
bool block_in_hand = false;


//  Map
WorldMap* game_map = nullptr;

constexpr float VIEW_DISTANCE = 100.0;


//  Settings
unsigned int WIDTH = 900;
unsigned int HEIGHT = 660;

void reshape(GLFWwindow* window, int width, int height);
void input(GLFWwindow* window);
void mouse(GLFWwindow* window, double xpos, double ypos);
void scroll(GLFWwindow* window, double xoffset, double yoffset);


//  Timer
float delta_time = 0.0f;
float last_frame = 0.0f;

game::TEXTURE_TYPE current_texture = game::BRICK;
bool hide_cube_to_place = false;





Sun sun(new SunViewBasic, (cos(glm::radians(45.0f)) * VIEW_DISTANCE) / 2.0);


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
    auto window = glfwCreateWindow(WIDTH, HEIGHT, "Cube Builder Game", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error creating window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    //  Set callbacks
    glfwSetFramebufferSizeCallback(window, reshape);
    glfwSetCursorPosCallback(window, mouse);
    glfwSetScrollCallback(window, scroll);

    //  Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //  Enable depth testing
    glEnable(GL_DEPTH_TEST);
    /***   End Intitializing  ***/


    game::Shader tileshader;
    tileshader.init("shaders/tile.vs", "shaders/tile.fs");



    //  CROSSHAIRS
    CrossHairs crosshairs;

    //  Disable mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    //  Configure game map
    game_map = new WorldMap(5);

    Slab* slab1 = new GrassSlab;
    //slab1->addElement(game::ROCK, glm::vec3(0.0, 0.0, 0.0));
    game_map->addSlab(slab1);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new WoodlandSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new WoodlandSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new WoodlandSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new WoodlandSlab);
    game_map->addSlab(new GrassSlab);
    game_map->fillRestOfMap();

    game::Shader shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", "basic");
    auto cube = GameResources::getCube2();
    GameResources::bind(game::WATER);

    auto tile = GameResources::getTile();

    auto shader2 = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", "noname");



    //  Set the initial position
    camera.setPos(glm::vec3(0.0f, 4.0f, 5.0f));

    //  cube with normals
    auto new_cube_shader = GameResources::loadShader("shaders/cube.vs", "shaders/cube.fs", "cube");
    auto new_cube = GameResources::getCube();



    //  Sun
    sun.setTheta(90.0f);

    //  Sky
    Sky sky;
    game::Shader sky_shader;
    sky_shader.init("shaders/sky.vs", "shaders/sky.fs");

    sky.enableSunrise();

    float cosview_distance = cos(glm::radians(45.0f)) * VIEW_DISTANCE;

    SkyController skycontrol(glm::vec4(0.3, 0.7, 1.0, 1.0),
                         glm::vec4(0.05, 0.05, 0.05, 1.0),
                         glm::vec4(1.0, 0.7, 0.7, 1.0),
                         glm::vec4(1.0, 0.3, 0.3, 1.0));


    /*********** MAIN LOOP  ***********************/
    while (!glfwWindowShouldClose(window)) {

        //  Set background color
        glClearColor(0.0, 1.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //  Update camera
        camera.update();

        //  Set Projection Matrix
        GameResources::setProjectionMatrix(glm::perspective(glm::radians(45.0f),
                                                            float(WIDTH) / float(HEIGHT),
                                                            0.1f, VIEW_DISTANCE));

        //  Set View Matrix
        // GameResources::setViewMatrix(glm::lookAt(camera.pos, camera.pos + camera.dir, camera.up));
        GameResources::setViewMatrix(glm::lookAt(camera.pos(), camera.pos() + camera.dir(), camera.up()));


        //  Draw World Map
        //  game_map->draw(camera.pos);
        game_map->draw(camera.pos());

        if (!hide_cube_to_place) {
            //  Draw Cube to place
            auto model = glm::mat4(1.0f);
            auto shift = game_map->getMousePointerLocation(camera, ADD);
            auto shift_prime = glm::vec3(int(shift.x)+0.5, int(shift.y), int(shift.z)+0.5);
            model = glm::translate(model, shift_prime);
            auto shader = GameResources::loadShader("shaders/s1.vs", "shaders/s1.fs", game::CUBE_SHADER_NO_NORMALS);
            auto cube = GameResources::getCubeWithoutNormals();
            shader.use();
            GameResources::bind(current_texture);
            glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                               1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
            glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                               1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));
            glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                               1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(cube.vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //  Draw sun
        sun.draw();


        //  Update and Draw Sky
        skycontrol.update(GameResources::getLightAngle());
        //skycontrol.draw(cosview_distance, camera.pos);
        skycontrol.draw(cosview_distance, camera.pos());

        //  Draw cross hairs
        crosshairs.draw();

        //  Swap buffers and poll events
        glfwSwapBuffers(window);
        //  Process input
        input(window);
        glfwPollEvents();
    }

    //  Clean up resources
    if (game_map != nullptr) delete game_map;

    GameResources::destroy();
    sky.destroy();

    glfwTerminate();
    return 0;
}

/***************************************************************
***   RESHAPE   ************************************************
***************************************************************/
void reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
}

/****************************************************************
***   INPUT   ***************************************************
****************************************************************/
void input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    float sun_speed = 3.0;

    //  Update the sun
    sun.update(sun_speed* delta_time, camera.pos());
    GameResources::setLightAngle(sun.theta());
    GameResources::setLightPos(sun.getPos());
    GameResources::setPlayerPos(camera.pos());


    //  Get the up and direction vectors
    glm::vec3 direction = glm::vec3(camera.dir().x, 0.0f, camera.dir().z);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    //  Camera speed
    static float speed = 0.1 * delta_time;

    //  The output_vector is the amount that the camera will move
    glm::vec3 output_vector = glm::vec3(0.0, 0.0, 0.0);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        output_vector += speed * glm::normalize(direction);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        output_vector -= speed * glm::normalize(direction);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        output_vector -= glm::normalize(glm::cross(direction, up)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        output_vector += glm::normalize(glm::cross(direction, up)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        output_vector += glm::vec3(0.0f, speed, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        output_vector -= glm::vec3(0.0f, speed, 0.0f);
    }

    //  Update the camera position
    camera.updatePos(output_vector);

    static bool p_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !p_pressed) {
        p_pressed = true;
        if (paused) {
            paused = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            paused = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && p_pressed) {
        p_pressed = false;
    }

    //  If collision change camera back to previous position
    if (game_map->collision(camera.pos())) {
        camera.updatePos(-output_vector);
    }

    //  place block
    static bool f_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !f_pressed) {
        auto mouse_ptr = game_map->getMousePointerLocation(camera, ADD);
        if (mouse_ptr.x - -1.0 > 0.0001 && mouse_ptr.y - -1.0 > 0.0001 && mouse_ptr.z - -1.0 > 0.0001) {
            game_map->addCube(current_texture, camera.pos(), mouse_ptr);
        }
        f_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && f_pressed) {
        f_pressed =false;
    }

    //  remove block
    static bool r_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !r_pressed) {
        auto mouse_ptr = game_map->getMousePointerLocation(camera, REMOVE);
        game_map->removeCube(mouse_ptr);
        r_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE && r_pressed) {
        r_pressed = false;
    }

    static bool zero_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        if (!zero_pressed) {
            zero_pressed = true;
            if (hide_cube_to_place) hide_cube_to_place = false;
            else hide_cube_to_place = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_RELEASE) {
        if (zero_pressed) zero_pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        current_texture = game::WATER;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        current_texture = game::GRASS;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        current_texture = game::DESERT;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        current_texture = game::DIRT;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        current_texture = game::ROCK;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        current_texture = game::ROAD;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        current_texture = game::BRICK;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
        current_texture = game::WOOD;
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        current_texture = game::WALL;
    }
}

/******************************************************************
***   MOUSE   *****************************************************
******************************************************************/
void mouse(GLFWwindow* window, double xpos, double ypos) {
    static float last_x = float(WIDTH) / 2.0;
    static float last_y = float (HEIGHT) / 2.0;
    float sensitivity = 0.15f;

    camera.updateYaw((xpos - last_x) * sensitivity);
    camera.updatePitch((last_y - ypos) * sensitivity);


    if (camera.pitch() > 89.0) {
        camera.setPitch(89.0);
    }
    if (camera.pitch() < -89.0) {
        camera.setPitch(-89.0);
    }

    last_x = xpos;
    last_y = ypos;
}

/*******************************************************************
***   SCROLL   *****************************************************
*******************************************************************/
void scroll(GLFWwindow* window, double xoffset, double yoffset) {

}
