#include "CrossHairs.h"

CrossHairs::CrossHairs() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shader.init("shaders/line.vs", "shaders/line.fs");
    glUseProgram(shader.id());
    glUniform4f(glGetUniformLocation(shader.id(), "color"), 0.5f, 0.9f, 0.5f, 1.0f);
}

CrossHairs::~CrossHairs() {}

void CrossHairs::draw() {
    glUseProgram(shader.id());
    glBindVertexArray(vao);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 4);
}

void CrossHairs::destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
