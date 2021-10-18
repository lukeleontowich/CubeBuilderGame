#ifndef SUNVIEW_H
#define SUNVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sun.h"
class Sun;

class SunView {
public:
    SunView();
    virtual ~SunView();
    virtual void draw(Sun* sun) = 0;
};

#endif // SUNVIEW_H
