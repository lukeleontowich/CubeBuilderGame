/*****************************************************
** Project: Cube Builder Game
** File: Sun.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Contains information of Sun position
*****************************************************/

#ifndef SUN_H
#define SUN_H

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//  forward delaration
#include "SunView.h"
class SunView;

class Sun {
private:
    //  Object that implements drawing the Sun
    SunView* view = nullptr;

    //  Position of the Sun
    glm::vec3 pos;

    //  Angle of the sun
    float _theta;

    //  Distance of the sun from the player
    float _distance;

public:
    /** Constructor  **/
    explicit Sun(SunView* ptr, float distance);

    /**  Desctructor  **/
    ~Sun();

    /** draw()
    ** @param none
    ** @return void
    ** Description: Draws the sun, the SunView* view implements the method
    **/
    void draw();

    /** theta()
    ** @param none
    ** @return float
    ** Description: Returns angle of the sun to the ground
    **/
    float theta() {return _theta;}

    /** setTheta()
    ** @param const float&
    ** @return void
    ** Description: Set the angle of the sun
    **/
    void setTheta(const float& t) {_theta = t;}

    /** getPos()
    ** @param none
    ** @return glm::vec3
    ** Description: Returns the position of the sun
    **/
    glm::vec3 getPos() {return pos;}

    /** update()
    ** @param float, const glm::vec3&
    ** @return none
    ** Description: Updates the angle of the sun based on a given spd
    ** Updates the sun position relative to the camera position
    **/
    void update(float spd, const glm::vec3& camera_pos);
};

#endif // SUN_H
