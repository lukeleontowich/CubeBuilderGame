/*****************************************************
** Project: Cube Builder Game
** File: GameController.h
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Takes in user input to control the game
*****************************************************/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameResources.h"

class CubeBuilderGame;
#include "CubeBuilderGame.h"


class GameController {
private:
    //  button presses tp prevent sticky keys
    bool p_pressed = false;
    bool f_pressed = false;
    bool r_pressed = false;
    bool zero_pressed = false;

    //  State of game
    bool paused = false;

    //  Variables needed for mouse movement
    float last_x;
    float last_y;
    float sensitivity = 0.15f;


    /** movement()
    ** @param GLFWwindow*, CubeBuilderGame*
    ** @return void
    ** Description: Player's input from keyboard for movement
    **/
    void movement(GLFWwindow* window, CubeBuilderGame* cubegame);

    /** pause()
    ** @param GLFWwindow*
    ** @return void
    ** Description: Checks player input for paused game selection
    **/
    void pause(GLFWwindow* window);

    /** addCube()
    ** @param GLFWwindow*, CubeBuilderGame*
    ** @return void
    ** Description: Checks player input for add Cube condition
    **/
    void addCube(GLFWwindow* window, CubeBuilderGame* cubegame);

    /** removeCube()
    ** @param GLFWwindow*, CubeBuilderGame*
    ** @return void
    ** Description: Checks player input for a remove cube condition
    **/
    void removeCube(GLFWwindow* window, CubeBuilderGame* cubegame);

    /** hideBlockInHand()
    ** @param GLFWwindow*, CubeBuilderGame*
    ** @return void
    ** Description: Checks player input to see if block in hand should be hidden/ unhidden
    **/
    void hideBlockInHand(GLFWwindow* window, CubeBuilderGame* cubegame);

    /** textureInHand()
    ** @param GLFWwindow*, CubeBuilderGame
    ** @return void
    ** Description: Checks player input to see if texture in hand needs to change
    **/
    void textureInHand(GLFWwindow* window, CubeBuilderGame* cubegame);

public:
    /** Constructor  **/
    GameController();

    /** Desctructor  **/
    ~GameController();

    /** input()
    ** @param GLFWwindow*, CubeBuidlerGame*
    ** @return void
    ** Description: Oraganizes and calls the private functions declared above
    **/
    void input(GLFWwindow* window, CubeBuilderGame* cubegame);

    /** mouse()
    ** @param Window and mouse position
    ** @return void
    ** Description: Handles mouse movement
    **/
    void mouse(GLFWwindow* window, double xpos, double ypos, CubeBuilderGame* cubegame);
};

#endif // GAMECONTROLLER_H
