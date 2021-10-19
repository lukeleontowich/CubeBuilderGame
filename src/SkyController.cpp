/*****************************************************
** Project: Cube Builder Game
** File: SkyController.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of SkyController class
*****************************************************/

#include "SkyController.h"

SkyController::SkyController(const glm::vec4& day,
                             const glm::vec4& night,
                             const glm::vec4& sunrise,
                             const glm::vec4& sunset) {
    sky = new Sky;
    daycolor = day;
    nightcolor = night;
    sunrisecolor = sunrise;
    sunsetcolor = sunset;

    night_to_sunrise = (sunrisecolor - nightcolor) / game::ANGLE_OF_SUNSETRISE;
    sunrise_to_day = (daycolor - sunrisecolor) / game::ANGLE_OF_SUNSETRISE;
    day_to_sunset = (sunsetcolor - daycolor) / game::ANGLE_OF_SUNSETRISE;
    sunset_to_night = (nightcolor - sunsetcolor) / game::ANGLE_OF_SUNSETRISE;

    night_to_day = (daycolor - nightcolor) / (2.0f * game::ANGLE_OF_SUNSETRISE);
    day_to_night = (nightcolor - daycolor) / (2.0f * game::ANGLE_OF_SUNSETRISE);
}

SkyController::~SkyController() {
    if (sky != nullptr) {
        delete sky;
    }
}


void SkyController::update(const float& theta) {
    //  sunrise start point to sunrise mid-point
    if (theta >= 360.0 - game::ANGLE_OF_SUNSETRISE && theta < 360.0) {
        sky->enableSunrise();
        sky->disableSunset();

        float distance_angle = game::ANGLE_OF_SUNSETRISE - (360.0 - theta);

        glm::vec4 temp = night_to_sunrise * distance_angle;
        sky->setSunriseColor(nightcolor + temp);

        temp = night_to_day * distance_angle;
        sky->update(nightcolor + temp);

    //  Sunrise mid-point to sunrise end-point/ day start-point
    } else if (theta >= 0.0 && theta < game::ANGLE_OF_SUNSETRISE) {
        sky->enableSunrise();
        sky->disableSunset();

        float distance_angle = theta;

        glm::vec4 temp = sunrise_to_day * distance_angle;
        sky->setSunriseColor(sunrisecolor + temp);

        temp = night_to_day * (distance_angle + game::ANGLE_OF_SUNSETRISE);
        sky->update(nightcolor + temp);

    //  Day start-point to day end-point/ sunset start-point
    } else if (theta >= game::ANGLE_OF_SUNSETRISE && theta < 180.0 - game::ANGLE_OF_SUNSETRISE) {
        sky->disableSunrise();
        sky->disableSunset();
        sky->update(daycolor);

    //  Sunset start-point to sunset mid-point
    } else if (theta >= 180.0 - game::ANGLE_OF_SUNSETRISE && theta < 180.0) {
        sky->disableSunrise();
        sky->enableSunset();


        float distance_angle = game::ANGLE_OF_SUNSETRISE - (180.0 - theta);

        glm::vec4 temp = day_to_sunset * distance_angle;
        sky->setSunsetColor(daycolor + temp);

        temp = day_to_night * distance_angle;
        sky->update(daycolor + temp);

    //  Sunset mid-point to sunset end-point/ night start-point
    } else if (theta >= 180.0 && theta < 180.0 + game::ANGLE_OF_SUNSETRISE) {
        sky->disableSunrise();
        sky->enableSunset();

        float distance_angle = theta - 180.0;

        glm::vec4 temp = sunset_to_night * distance_angle;
        sky->setSunsetColor(sunsetcolor + temp);

        temp = day_to_night * (distance_angle + game::ANGLE_OF_SUNSETRISE);
        sky->update(daycolor + temp);

    //  Night start-point to night end-point / sunrise start-point
    } else {
        sky->disableSunrise();
        sky->disableSunset();
        sky->update(nightcolor);
    }
}

void SkyController::draw(const float& sky_size, const glm::vec3& pos) {
    auto shader = GameResources::loadShader("shaders/sky.vs", "shaders/sky.fs", game::SKY_SHADER);

    shader.use();

    glBindVertexArray(sky->vao());

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "view"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"),
                       1, GL_FALSE, glm::value_ptr(GameResources::getProjectionMatrix()));

    auto model = glm::mat4(1.0f);

    //  Sky tracks the players position
    model = glm::translate(model, glm::vec3(pos.x, sky_size/ 2.0, pos.z));

    auto temp = glm::vec3(sky_size);
    model = glm::scale(model, temp);

    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                       1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

