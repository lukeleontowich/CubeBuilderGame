#include "Sun.h"

Sun::Sun(SunView* ptr, float distance) {
    view = ptr;
    _distance = distance;
    _theta = 0;
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

Sun::~Sun() {
    if (view != nullptr) delete view;
}

void Sun::draw() {
    view->draw(this);
}

void Sun::update(float spd, const glm::vec3& camera_pos) {
    _theta += spd;
    if (_theta > 359.99999999f) {
        _theta = 0.1f;
    }
    if (_theta < 0.000000000001f) {
        _theta = 359.0f;
    }
    pos.z = camera_pos.z;
    pos.x = cos(glm::radians(_theta)) * _distance + camera_pos.x;
    pos.y = sin(glm::radians(_theta)) * _distance;
}
