/*****************************************************
** Project: Cube Builder Game
** File: CubeBuilderGame.cpp
** Author: Luke Leontowich
** Date: November 12, 2021
** Description: Implements CubeBuilderGame.h
*****************************************************/

#include "CubeBuilderGame.h"

CubeBuilderGame::CubeBuilderGame() {
    _camera = new Camera();

    //  Set camera initial position
    _camera->setPos(glm::vec3(0.0f, 4.0f, 5.0f));

    _hand = new Hand;

    //  Initialize sun properties
    _sun = new Sun(new SunViewBasic, (cos(glm::radians(45.0f)) * VIEW_DISTANCE) / 2.0);

    //  Build a world map
    _worldmap = WorldMapGenerator::generateWorld(game::BASIC_SMALL);

    gamecontroller = new GameController;

    //  Initialize sky and sky controller
    _sky = new Sky;
    _skycontroller = new SkyController(glm::vec4(0.3, 0.7, 1.0, 1.0),
                                       glm::vec4(0.05, 0.05, 0.05, 1.0),
                                       glm::vec4(1.0, 0.7, 0.7, 1.0),
                                       glm::vec4(1.0, 0.3, 0.3, 1.0));
    _crosshairs = new CrossHairs();

    //  Assign a value, doing the calculation once
    cosview_distance = cos(glm::radians(45.0f)) * VIEW_DISTANCE;
}

CubeBuilderGame::CubeBuilderGame(game::WORLD_MAP_SEED seed) {
    _camera = new Camera();

    //  Set camera initial position
    _camera->setPos(glm::vec3(0.0f, 4.0f, 5.0f));

    _hand = new Hand;

    //  Initialize sun properties
    _sun = new Sun(new SunViewBasic, (cos(glm::radians(45.0f)) * VIEW_DISTANCE) / 2.0);

    //  Build a world map
    _worldmap = WorldMapGenerator::generateWorld(seed);

    gamecontroller = new GameController;

    //  Initialize sky and sky controller
    _sky = new Sky;
    _skycontroller = new SkyController(glm::vec4(0.3, 0.7, 1.0, 1.0),
                                       glm::vec4(0.05, 0.05, 0.05, 1.0),
                                       glm::vec4(1.0, 0.7, 0.7, 1.0),
                                       glm::vec4(1.0, 0.3, 0.3, 1.0));
    _crosshairs = new CrossHairs();

    //  Assign a value, doing the calculation once
    cosview_distance = cos(glm::radians(45.0f)) * VIEW_DISTANCE;
}


CubeBuilderGame::~CubeBuilderGame() {
    if (_camera != nullptr) delete _camera;
    if (_hand != nullptr) delete _hand;
    if (_sun != nullptr) delete _sun;
    if (_worldmap != nullptr) delete _worldmap;
    if (_sky != nullptr) delete _sky;
    if (_skycontroller != nullptr) delete _skycontroller;
    if (_crosshairs != nullptr) delete _crosshairs;
    if (gamecontroller != nullptr) delete gamecontroller;
}

void CubeBuilderGame::update(const float& delta_time) {
    _camera->update();

    //  Set View Matrix
    GameResources::setViewMatrix(glm::lookAt(_camera->pos(), _camera->pos() + _camera->dir(), _camera->up()));

    //  Update and Draw Sky
    _skycontroller->update(GameResources::getLightAngle());

    //  Set speed
    _speed = 5.0* delta_time;

    //  Update the sun position
    _sun->update(sun_speed* delta_time, _camera->pos());

    //  Send sun and player information to global information
    GameResources::setLightAngle(_sun->theta());
    GameResources::setLightPos(_sun->getPos());
    GameResources::setPlayerPos(_camera->pos());
}

void CubeBuilderGame::input(GLFWwindow* window) {
    gamecontroller->input(window, this);
}

void CubeBuilderGame::mouse(GLFWwindow* window, double xpos, double ypos) {
    gamecontroller->mouse(window, xpos, ypos, this);
}

void CubeBuilderGame::draw() {
    //  Draw world map
    _worldmap->draw(_camera->pos());

    //  Draw the block in player's hand
    auto shift = _worldmap->getMousePointerLocation(*_camera, ADD);
    _hand->draw(shift);

    //  Draw the sun and the sky
    _sun->draw();
    _skycontroller->draw(cosview_distance, _camera->pos());

    //  Draw the crosshairs
    _crosshairs->draw();
}

void CubeBuilderGame::destroy() {
    _sky->destroy();
}
