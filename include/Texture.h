/*****************************************************
** Project: Cube Builder Game
** File: Texture.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: First version of Texture. See Texture2D.h
** for current in use version. Other elements within the
** namespace game are being used, such as; TEXTURE_TYPE,
** and the name of the texture files
*****************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>


namespace game {

static constexpr unsigned int NUM_TEXTURES = 10;
enum TEXTURE_TYPE {
    WATER = 0,
    GRASS = 1,
    DESERT = 2,
    DIRT = 3,
    ROCK = 4,
    ROAD = 5,
    BRICK = 6,
    WOOD = 7,
    WALL = 8,
    WOODLAND = 9
};

//  https://www.pinterest.ca/pin/407223991276902643/
static const std::string water_file = "textures/water2.jpeg";

//  Homemade
static const std::string grass_file = "textures/grasslight2.jpg";

//  https://www.tilingtextures.com/gravel-decorated-exterior-plaster/
static const std::string desert_file = "textures/sand.jpg";

//  https://www.tilingtextures.com/warm-sandy-plaster/
static const std::string dirt_file = "textures/dirt.jpg";

//  https://www.tilingtextures.com/rectangular-stone-wall/
static const std::string rock_file = "textures/rock.jpg";

//  https://www.tilingtextures.com/plastering-with-fine-grained-pebbles/
static const std::string road_file = "textures/road.jpg";

//  https://www.tilingtextures.com/decorative-orange-brick-wall/
static const std::string brick_file = "textures/brick.jpg";

//  https://www.tilingtextures.com/exterior-cabin-wainscot/
static const std::string wood_file = "textures/wood.jpg";

//  https://www.tilingtextures.com/gravel-decorated-exterior-plaster/
static const std::string wall_file = "textures/wall.jpg";

//  Homemade
static const std::string woodland_file = "textures/grassdark2.jpg";

enum TEXTURE_ERROR {
    TEXTURE_SUCCESS = 0,
    IN_COMPATIBLE_SIZE = 1,
    WATER_FILE_NOT_FOUND = 10,
    GRASS_FILE_NOT_FOUND = 11,
    DESERT_FILE_NOT_FOUND = 12,
    DIRT_FILE_NOT_FOUND = 13,
    ROCK_FILE_NOT_FOUND = 14,
    ROAD_FILE_NOT_FOUND = 15,
    BRICK_FILE_NOT_FOUND = 16,
    WOOD_FILE_NOT_FOUND = 17,
    WALL_FILE_NOT_FOUND = 18,
    WOODLAND_FILE_NOT_FOUND = 19
};

class Texture {
public:
    explicit Texture(unsigned int num_textures);
    ~Texture();
    int addTexture(unsigned int index, std::string file_path);
    unsigned int* getTextures() {return textures;}
    int bind(unsigned int index);
    TEXTURE_ERROR makeGameTextures();
private:
    unsigned int* textures = nullptr;
    unsigned int n;
};
}
#endif // TEXTURE_H
