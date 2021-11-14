/*****************************************************
** Project: Cube Builder Game
** File: CubeBuilderGame.h
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Stores non global resources and
** controls the game.
*****************************************************/

#ifndef CUBEBUILDERGAME_H
#define CUBEBUILDERGAME_H

#include "GameResources.h"
#include "Camera.h"
#include "Hand.h"
#include "Sun.h"
#include "WorldMap.h"
#include "Sky.h"
#include "SkyController.h"
#include "CrossHairs.h"
#include "WorldMapGenerator.h"

class GameController;
#include "GameController.h"

//  Variable needed for sun and sky calculations
constexpr float VIEW_DISTANCE = 100.0;

class CubeBuilderGame {
private:
    //  Player camera
    Camera* _camera = nullptr;

    //  Block in hand object
    Hand* _hand = nullptr;

    //  Sun
    Sun* _sun = nullptr;

    //  Map
    WorldMap* _worldmap = nullptr;

    //  Sky
    Sky* _sky = nullptr;

    //  Sky contoller
    SkyController* _skycontroller = nullptr;

    //  Cross hairs
    CrossHairs* _crosshairs = nullptr;

    //  Game controller
    GameController* gamecontroller = nullptr;

    //  Paused state
    bool paused = false;

    //  Speed that the sun travels
    float sun_speed = 3.0;

    //  Speed of player, will be determined by deltatime during gameplay
    float _speed;

    //  Variable needed for sky/ sun calculations
    float cosview_distance;

public:
    /**  Constructors  **/
    //  Defaults to BASIC_SMALL World
    CubeBuilderGame();
    CubeBuilderGame(game::WORLD_MAP_SEED seed);


    /**  Destructor  **/
    ~CubeBuilderGame();

    /**  update()
    ** @param const float&, delta time
    ** @return void
    ** Description: Updates game resources based on delta_time
    **/
    void update(const float& delta_time);

    /** input()
    ** @param Window
    ** @return void
    ** Description: updates game based on player input. The controller of the game
    **/
    void input(GLFWwindow* window);

    /** mouse()
    ** @param Window, xpos, ypos of mouse
    ** @return void
    ** Description: Mouse movement of player, handled by GameController
    **/
   void mouse(GLFWwindow* window, double xpos, double ypos);

    /** draw()
    ** @param none
    ** @return void
    ** Description: Draws the frame
    **/
    void draw();

    /** destroy()
    ** @param none
    ** @return void
    ** Description: cleans up resources not taken care of by delete. (vbo's, voa's, etc)
    **/
    void destroy();

    /**  Getter functions  **/
    Camera* camera() const {return _camera;}
    Hand* hand() const {return _hand;}
    Sun* sun() const {return _sun;}
    WorldMap* worldmap() const {return _worldmap;}
    Sky* sky() const {return _sky;}
    SkyController* skycontroller() const {return _skycontroller;}
    CrossHairs* crosshairs() const {return _crosshairs;}
    float speed() {return _speed;}
};

#endif // CUBEBUILDERGAME_H
