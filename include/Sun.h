#ifndef SUN_H
#define SUN_H

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SunView.h"
class SunView;

class Sun {
public:
    Sun(SunView* ptr, float distance);
    ~Sun();
    void draw();
    float theta() {return _theta;}
    void setTheta(const float& t) {_theta = t;}
    glm::vec3 getPos() {return pos;}
    void update(float spd, const glm::vec3& camera_pos);
private:
    SunView* view = nullptr;
    glm::vec3 pos;
    float _theta;
    float _distance;
};

#endif // SUN_H
