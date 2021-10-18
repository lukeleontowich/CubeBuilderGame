#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

namespace game {

class Shader {
public:
    Shader();
    ~Shader();
    unsigned int id() {return _id;}
    bool init(std::string v_path, std::string f_path);
    void deleteShader();
    void use();
private:
    unsigned int _id;
    std::string getCode(std::string path);
    bool compiled(unsigned int shader, const char* msg);
};
}
#endif // SHADER_H
