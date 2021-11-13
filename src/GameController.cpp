/*****************************************************
** Project: Cube Builder Game
** File: GameController.cpp
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Implements GameController.h
*****************************************************/

#include "GameController.h"

GameController::GameController() {
    last_x = float(GameResources::WIDTH) / 2.0;
    last_y = float (GameResources::HEIGHT) / 2.0;
}

GameController::~GameController() {}

void GameController::input(GLFWwindow* window, CubeBuilderGame* cubegame) {
    //  Check to see if game is closed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    //  get resources
    this->pause(window);
    if (!paused) {
        this->movement(window, cubegame);
        this->addCube(window, cubegame);
        this->removeCube(window, cubegame);
        this->textureInHand(window, cubegame);
        this->hideBlockInHand(window, cubegame);
    }
}

void GameController::mouse(GLFWwindow* window, double xpos, double ypos, CubeBuilderGame* cubegame) {
    //  If game paused do nothing
    if (paused) return;

    auto camera = cubegame->camera();

    camera->updateYaw((xpos - last_x) * sensitivity);
    camera->updatePitch((last_y - ypos) * sensitivity);


    if (camera->pitch() > 89.0) {
        camera->setPitch(89.0);
    }
    if (camera->pitch() < -89.0) {
        camera->setPitch(-89.0);
    }

    last_x = xpos;
    last_y = ypos;
}

void GameController::movement(GLFWwindow* window, CubeBuilderGame* cubegame) {
    //  Get camera
    auto camera = cubegame->camera();
    auto speed = cubegame->speed();
    auto worldmap = cubegame->worldmap();

    //  Get the up and direction vectors
    glm::vec3 direction = glm::vec3(camera->dir().x, 0.0f, camera->dir().z);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

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
    camera->updatePos(output_vector);

    //  If collision change camera back to previous position
    if (worldmap->collision(camera->pos())) {
        camera->updatePos(-output_vector);
    }
}

void GameController::pause(GLFWwindow* window) {
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
}

void GameController::addCube(GLFWwindow* window, CubeBuilderGame* cubegame) {
    //  Get resources
    auto camera = cubegame->camera();
    auto worldmap = cubegame->worldmap();
    auto hand = cubegame->hand();

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !f_pressed) {
        auto mouse_ptr = worldmap->getMousePointerLocation(*camera, ADD);
        if (mouse_ptr.x - -1.0 > 0.0001 && mouse_ptr.y - -1.0 > 0.0001 && mouse_ptr.z - -1.0 > 0.0001) {
            worldmap->addCube(hand->current_texture(), camera->pos(), mouse_ptr);
        }
        f_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && f_pressed) {
        f_pressed =false;
    }
}

void GameController::removeCube(GLFWwindow* window, CubeBuilderGame* cubegame) {
    //  Get resources
    auto camera = cubegame->camera();
    auto worldmap = cubegame->worldmap();

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !r_pressed) {
        auto mouse_ptr = worldmap->getMousePointerLocation(*camera, REMOVE);
        worldmap->removeCube(mouse_ptr);
        r_pressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE && r_pressed) {
        r_pressed = false;
    }
}

void GameController::hideBlockInHand(GLFWwindow* window, CubeBuilderGame* cubegame) {
    //  get resources
    auto hand = cubegame->hand();

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        if (!zero_pressed) {
            zero_pressed = true;
            if (hand->block_in_hand()) hand->changeBlockInHand(false);
            else hand->changeBlockInHand(true);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_RELEASE) {
        if (zero_pressed) zero_pressed = false;
    }
}

void GameController::textureInHand(GLFWwindow* window, CubeBuilderGame* cubegame) {
    //  get hand
    auto hand = cubegame->hand();

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        hand->changeTexture(game::WATER);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        hand->changeTexture(game::GRASS);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        hand->changeTexture(game::DESERT);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        hand->changeTexture(game::DIRT);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        hand->changeTexture(game::ROCK);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        hand->changeTexture(game::ROAD);
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        hand->changeTexture(game::BRICK);
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
        hand->changeTexture(game::WOOD);
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        hand->changeTexture(game::WALL);
    }
}


