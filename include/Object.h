#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>
/*
typedef struct {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec4 color;
} Vertex;


class Object {
public:
    explicit Object(const std::string& file);
    ~Object();
    bool init();
private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    unsigned int _vao, _vbo, _ebo;
    std::string _filename;
};
*/
#endif // OBJECT_H
