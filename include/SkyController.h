/*****************************************************
** Project: Cube Builder Game
** File: SkyController.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Controls the Color of the sky
*****************************************************/

#ifndef SKYCONTROLLER_H
#define SKYCONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "Sky.h"
#include "GameResources.h"

namespace game {
    //  Angle at which the sunset/ sunrise begins
    constexpr float ANGLE_OF_SUNSETRISE = 30.0;
}

class SkyController {
private:
    //  Sky object
    Sky* sky = nullptr;

    //  Colors of day, night, sunrise, sunset
    glm::vec4 daycolor;
    glm::vec4 nightcolor;
    glm::vec4 sunrisecolor;
    glm::vec4 sunsetcolor;

    //  Transitional colors
    glm::vec4 night_to_sunrise;
    glm::vec4 sunrise_to_day;
    glm::vec4 day_to_sunset;
    glm::vec4 sunset_to_night;
    glm::vec4 night_to_day;
    glm::vec4 day_to_night;

public:
    /**  Constructor  **/
    explicit SkyController(const glm::vec4& daycol,
                           const glm::vec4& nightcol,
                           const glm::vec4& sunrisecol,
                           const glm::vec4& sunsetcol);

    /** Desctructor  **/
    ~SkyController();

    /** update()
    ** @param const float& theta
    ** @return void
    ** Description: Updates the color of the sky and the state of the sky
    ** Based on the angle of the sun (or any celestial object)
    **/
    void update(const float& theta);

    /** draw()
    ** @param const float& sky_size, const glm::vec3& pos
    ** @return void
    ** Description: Draws the sky
    **/
    void draw(const float& sky_size, const glm::vec3& pos);
};

#endif // SKYCONTROLLER_H
