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
    constexpr float ANGLE_OF_SUNSETRISE = 30.0;
}

class SkyController {
public:
    explicit SkyController(const glm::vec4& daycol,
                           const glm::vec4& nightcol,
                           const glm::vec4& sunrisecol,
                           const glm::vec4& sunsetcol);
    ~SkyController();
    void update(const float& theta);
    void draw(const float& sky_size, const glm::vec3& pos);
private:
    Sky* sky = nullptr;
    glm::vec4 daycolor;
    glm::vec4 nightcolor;
    glm::vec4 sunrisecolor;
    glm::vec4 sunsetcolor;

    glm::vec4 night_to_sunrise;
    glm::vec4 sunrise_to_day;
    glm::vec4 day_to_sunset;
    glm::vec4 sunset_to_night;

    glm::vec4 night_to_day;
    glm::vec4 day_to_night;
};

#endif // SKYCONTROLLER_H
