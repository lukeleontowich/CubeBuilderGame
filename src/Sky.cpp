#include "Sky.h"

Sky::Sky() {
    //  set color to a shade of blue
    glm::vec4 color = glm::vec4(0.5, 0.7, 1.0, 1.0);

    color1[0] = color.x;
    color1[1] = color.y;
    color1[2] = color.z;
    color1[3] = color.w;

    color2[0] = color.x;
    color2[1] = color.y;
    color2[2] = color.z;
    color2[3] = color.w;

    color3[0] = color.x;
    color3[1] = color.y;
    color3[2] = color.z;
    color3[3] = color.w;

    color4[0] = color.x;
    color4[1] = color.y;
    color4[2] = color.z;
    color4[3] = color.w;

    color5[0] = color.x;
    color5[1] = color.y;
    color5[2] = color.z;
    color5[3] = color.w;

    color6[0] = color.x;
    color6[1] = color.y;
    color6[2] = color.z;
    color6[3] = color.w;

    color7[0] = color.x;
    color7[1] = color.y;
    color7[2] = color.z;
    color7[3] = color.w;

    color8[0] = color.x;
    color8[1] = color.y;
    color8[2] = color.z;
    color8[3] = color.w;


    sunrise_color = glm::vec4(1.0, 0.5, 0.5, 1.0);
    sunset_color = glm::vec4(1.0, 0.5, 0.5, 1.0);

    // initialize
    this->init();
}

Sky::~Sky() {}

void Sky::init() {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices)+(sizeof(color1)*8),
                 0, GL_STREAM_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+(sizeof(color1)*8), 0, GL_STREAM_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color1), &color1);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+ sizeof(color1), sizeof(color2), &color2);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+(2*sizeof(color1)), sizeof(color3), &color3);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+(3*sizeof(color1)), sizeof(color4), &color4);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+(4*sizeof(color1)), sizeof(color5), &color5);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+(5*sizeof(color1)), sizeof(color6), &color6);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+(6*sizeof(color1)), sizeof(color7), &color7);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+(7*sizeof(color1)), sizeof(color8), &color8);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(sizeof(vertices)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+sizeof(color1)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+(2*sizeof(color1))));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+(3*sizeof(color1))));
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+(4*sizeof(color1))));
    glEnableVertexAttribArray(5);

    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+(5*sizeof(color1))));
    glEnableVertexAttribArray(6);

    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+(6*sizeof(color1))));
    glEnableVertexAttribArray(7);

    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),
                          (void*)(sizeof(vertices)+(7*sizeof(color1))));
    glEnableVertexAttribArray(8);
}

void Sky::update(const glm::vec4& col) {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    //  update top corners
    color1[0] = col.x;
    color1[1] = col.y;
    color1[2] = col.z;
    color1[3] = col.w;
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color1), &color1);

    color2[0] = col.x;
    color2[1] = col.y;
    color2[2] = col.z;
    color2[3] = col.w;

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(color2), sizeof(color2), &color2);

    color3[0] = col.x;
    color3[1] = col.y;
    color3[2] = col.z;
    color3[3] = col.w;

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+2*sizeof(color3), sizeof(color3), &color3);

    color4[0] = col.x;
    color4[1] = col.y;
    color4[2] = col.z;
    color4[3] = col.w;
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+3*sizeof(color4), sizeof(color4), &color4);

    if (!sunset_state) {
        color5[0] = col.x;
        color5[1] = col.y;
        color5[2] = col.z;
        color5[3] = col.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+4*sizeof(color5), sizeof(color5), &color5);

        color6[0] = col.x;
        color6[1] = col.y;
        color6[2] = col.z;
        color6[3] = col.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+5*sizeof(color6), sizeof(color6), &color6);
    } else {
        color5[0] = sunset_color.x;
        color5[1] = sunset_color.y;
        color5[2] = sunset_color.z;
        color5[3] = sunset_color.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+4*sizeof(color5), sizeof(color5), &color5);

        color6[0] = sunset_color.x;
        color6[1] = sunset_color.y;
        color6[2] = sunset_color.z;
        color6[3] = sunset_color.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+5*sizeof(color6), sizeof(color6), &color6);
    }
    if (!sunrise_state) {
        color7[0] = col.x;
        color7[1] = col.y;
        color7[2] = col.z;
        color7[3] = col.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+6*sizeof(color7), sizeof(color7), &color7);

        color8[0] = col.x;
        color8[1] = col.y;
        color8[2] = col.z;
        color8[3] = col.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+7*sizeof(color8), sizeof(color8), &color8);
    } else {
        color7[0] = sunrise_color.x;
        color7[1] = sunrise_color.y;
        color7[2] = sunrise_color.z;
        color7[3] = sunrise_color.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+6*sizeof(color7), sizeof(color7), &color7);

        color8[0] = sunrise_color.x;
        color8[1] = sunrise_color.y;
        color8[2] = sunrise_color.z;
        color8[3] = sunrise_color.w;
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+7*sizeof(color8), sizeof(color8), &color8);
    }
}

void Sky::enableSunrise() {
    sunrise_state = true;
}
void Sky::disableSunrise() {
    sunrise_state = false;
}

void Sky::enableSunset() {
    sunset_state = true;
}

void Sky::disableSunset() {
    sunset_state = false;
}

void Sky::setSunriseColor(const glm::vec4& color) {
    sunrise_color = color;
}

void Sky::setSunsetColor(const glm::vec4& color) {
    sunset_color = color;
}

void Sky::destroy() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao);
}
