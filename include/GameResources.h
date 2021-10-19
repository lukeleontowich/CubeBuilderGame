/*********************************************************
** Project: Ultimate Mayor
** File: GameResources.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: **
** This class defines global game references.
** It is a version of the singleton design pattern, where
** each GameResource is initialized upon its first use.
** I'm doing this because it is faster to compile a shader
** once and keep using it. To re-compile shaders each frame'
** would be way to slow
** References: **
** The idea behind this is from learnopengl.com
** See the url below for more info
** https://learnopengl.com/In-Practice/2D-Game/Setting-up
***********************************************************/

#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>

#include "Shader.h"

#include "Cube.h"
#include "Texture.h"
#include "Model.h"
#include "Tile.h"
#include "Cube2.h"
#include "Texture2D.h"
#include "Tile2.h"
#include "Sun.h"
#include "SunViewBasic.h"

#include <string>

/** const strings and integers **/
namespace game {
    //  Used for mapping in the shader map
    static const std::string CUBE_SHADER_NORMALS = "cube_shader_normals";
    static const std::string CUBE_SHADER_NO_NORMALS = "cube_shader_nonormals";
    static const std::string TILE_SHADER_NORMALS = "tileshader_normals";
    static const std::string TILE_SHADER_NO_NORMALS = "tileshader_nonormals";
    static const std::string LINE_SHADER2D = "line_shader2D";
    static const std::string OBJECT_SHADER1 = "object_shader1";
    static const std::string SKY_SHADER = "sky_shader";

    //  Maximum view distance of the camera
    const float VIEW_DISTANCE = 100.0;

    //  Used for mapping in the objects map
    static const std::string MODEL_GRASS1 = "grass1_model";
    static const std::string MODEL_TREE1 = "tree1_model";
}


/** Class GameResources **/
class GameResources {
private:
    GameResources () {}

    //  shader map stores all the current shaders
    static std::map<std::string, game::Shader> shaders;

    //  object map stores all the current models
    static std::map<std::string, game::Model> objects;

    //  Cube info (Cube with normals)
    //  only want to bind the cube info to a vertex array once
    static Cube cube;
    static bool cube_init;

    //  Cube2 info (Cube without normals)
    static Cube2 cube2;
    static bool cube2_init;

    //  Textures to be initialized and loaded once and used many times
    static game::Texture2D textures;
    static bool textures_init;

    //  Tile info (with normals)
    //  only want to bind the tile info to a vertex array once
    static Tile tile;
    static bool tile_init;

    //  Tile info (without normals)
    static Tile2 tile2;
    static bool tile2_init;

    //  Light position
    //  Sun light position or possibly moon light
    static glm::vec3 lightpos;
    static float lightangle;

    //  player position
    static glm::vec3 playerpos;

    //  View and projection matrices
    static glm::mat4 view;
    static glm::mat4 projection;

public:
    /** bind()
    ** @param unsigned int index: index of the texture array to be bound by glBindTexture
    ** @return bool: returns true if binded correctly, false other wise.
    ** Description: Binds a texture
    **/
    static bool bind(unsigned int index);

    /** getCubeWithNormals()
    ** @param none
    ** @return Cube: global cube info
    ** Description: returns the cube info that contains the vao and vbo necessary to draw a cube
    **/
    static Cube getCube();
    static Cube getCubeWithNormals();

    /** getCubeWithoutNormals()
    ** @param none
    ** @return Cube2
    ** Description: Returns cube info without normals
    **/
    static Cube2 getCubeWithoutNormals();
    static Cube2 getCube2();

    /** getTileWithNormals()
    ** @param none
    ** @return Tile: return global tile info
    ** Description: returns the tile info that contains the vao and vbo necessary to draw a tile
    **/
    static Tile getTile();
    static Tile getTileWithNormals();

    /** getTileWithoutNormals()
    ** @param none
    ** @return Tile2
    ** Description: Returns the tile info without normals
    **/
    static Tile2 getTile2();
    static Tile2 getTileWithoutNormals();


    /** loadShader()
    ** @param const string&, const string&, const string&: file info and map index for shader
    ** @return Shader: return the desired shader
    ** Description: If shader is not in the map then load and compile shader and then return it.
    ** other wise return the already compiled shader. USE THE CONST STRINGS AT BEGINNING OF FILE
    ** TO ENSURE CORRECT SHADER, eg: auto shader = loadShader("vertex_path.vs", "frag_path.fs", game::OBJECT_SHADER1);
    **/
    static game::Shader loadShader(const std::string& vertex_path,
                                   const std::string& frag_path,
                                   const std::string& name);

    /** loadModel()
    ** @param const string& filename, const string& name: file name and name of map index
    ** @return Model: return the desired model
    ** Description: Similar to the loadShader but this loads a model. Again use the const strings
    ** for the name parameter.
    **/
    static game::Model loadModel(const std::string& filename, const std::string& name);

    /** Setters and Getters for light position and angle
    ** The light is the sun or moon in the sky
    **/
    static glm::vec3 getLightPos();
    static void setLightPos(const glm::vec3& pos);
    static float getLightAngle();
    static void setLightAngle(const float& angle);

    /** Setters and Getters for the player postion  **/
    static glm::vec3 getPlayerPos();
    static void setPlayerPos(const glm::vec3& pos);

    /** Setters and Getters for the view and projection matrices  **/
    static void setViewMatrix(glm::mat4 matrix);
    static void setProjectionMatrix(glm::mat4 projection);
    static glm::mat4 getViewMatrix();
    static glm::mat4 getProjectionMatrix();

    /** destroy()
    ** @param none
    ** @return void
    ** Desciption: deletes all allocated memory, vao's, vbo's, ebo's, textures...
    **/
    static void destroy();
};

#endif // GAMERESOURCES_H
