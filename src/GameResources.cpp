/*********************************************************
** Project: Cube Builder Game
** File: GameResources.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: **
** Implementation of GameResources class
***********************************************************/

#include "GameResources.h"

/**  Cube initialization **/
Cube GameResources::cube;
bool GameResources::cube_init = false;

/** getCube()
** If cube is not initialize then allocate the vertex array and vertex buffers
** Only want to allocate the memory once so once cube is initialized just return
** the Cube
**/
Cube GameResources::getCube() {
    if (!cube_init) {
        glGenVertexArrays(1, &cube.vao);
        glGenBuffers(1, &cube.vbo);

        glBindVertexArray(cube.vao);

        glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);

        cube_init = true;
    }
    return cube;
}

/** getCubeWithNormals()
** returns a cube with normals
** We need normals for lighting calculations
**/
Cube GameResources::getCubeWithNormals() {
    return getCube();
}

/** getCubeWithoutNormals()
** Returns a cube without normals
** This cube won't be affected by lighting
**/
Cube2 GameResources::getCubeWithoutNormals() {
    return getCube2();
}
/** Cube2 (Cube without normal) initialization **/
Cube2 GameResources::cube2;
bool GameResources::cube2_init = false;

/** getCube2()
** If cube2 is not initialize then allocate the vertex array and vertex buffers
** Only want to allocate the memory once so once cube is initialized just return
** the Cube2
**/
Cube2 GameResources::getCube2() {
    if (!cube2_init) {

        glGenVertexArrays(1, &cube2.vao);
        glGenBuffers(1, &cube2.vbo);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(cube2.vao);

        glBindBuffer(GL_ARRAY_BUFFER, cube2.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube2.vertices), cube2.vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        cube2_init = true;
    }
    return cube2;
}

/**  Initialize textures  **/
game::Texture2D GameResources::textures;
bool GameResources::textures_init = false;

/** bind()
** Binds a texture to be used
**/
bool GameResources::bind(unsigned int index) {
    if (!textures_init) {
        textures.init();
        textures_init = true;
    }
    return textures.bind(index);
}


/** Initialize shader map  **/
std::map<std::string, game::Shader> GameResources::shaders;


/** loadShader() **/
game::Shader GameResources::loadShader(const std::string& vertex_path,
                                       const std::string& frag_path,
                                       const std::string& name) {
    //  Check to see if shader is already in map. We don't want to keep compiling the same shader
    auto it = std::find_if(shaders.begin(), shaders.end(),
                           [&name](const std::pair<std::string, game::Shader>& p) {return name == p.first;});

    //  If iterator is NOT at the end then we have found the shader
    if (it != shaders.end()) {
        //  it is pointing at the correct shader so return it
        return (*it).second;

    //  Case that the iterator IS at the end
    //  Now we need to initialize the new shader and store it in the map
    } else {
        game::Shader shader;

        //  The init function takes care of compilation
        shader.init(vertex_path, frag_path);

        //  put new shader into map
        shaders[name] = shader;

        //  return new shader
        return shaders[name];
    }
}

/**  Tile initialization  **/
Tile GameResources::tile;
bool GameResources::tile_init = false;

/** getTile()
** If tile is not initialized, allocate the vao, vbo and ebo
**/
Tile GameResources::getTile() {
    if (!tile_init) {
        glGenVertexArrays(1, &tile.vao);
        glGenBuffers(1, &tile.vbo);
        glGenBuffers(1, &tile.ebo);

        glBindVertexArray(tile.vao);

        glBindBuffer(GL_ARRAY_BUFFER, tile.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tile.vertices), tile.vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tile.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tile.indices), tile.indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 *sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);

        tile_init = true;
    }
    return tile;
}

/** getTileWithNormals()  **/
Tile GameResources::getTileWithNormals() {
    return getTile();
}

/** Tiles without Normals  **/
Tile2 GameResources::tile2;
bool GameResources::tile2_init = false;

Tile2 GameResources::getTile2() {
    if (!tile2_init) {
        glGenVertexArrays(1, &tile2.vao);
        glGenBuffers(1, &tile2.vbo);
        glGenBuffers(1, &tile2.ebo);

        glBindVertexArray(tile2.vao);

        glBindBuffer(GL_ARRAY_BUFFER, tile2.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tile2.vertices), tile2.vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tile2.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tile2.indices), tile2.indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        tile2_init = true;
    }
    return tile2;
}

/** getTileWithoutNormals()  **/
Tile2 GameResources::getTileWithoutNormals() {
    return getTile2();
}


/**  Initialize light pos **/
glm::vec3 GameResources::lightpos = glm::vec3(0.0f, 0.0f, 0.0f);
float GameResources::lightangle = 0.0f;

/** getLightPos() **/
glm::vec3 GameResources::getLightPos() {
    return lightpos;
}

/** setLightPos()  **/
void GameResources::setLightPos(const glm::vec3& pos) {
    lightpos = pos;
}

/** getLightAngle()  **/
float GameResources::getLightAngle() {
    return lightangle;
}

/** setLightAngle()  **/
void GameResources::setLightAngle(const float& angle) {
    lightangle = angle;
}


/**  Initialize player position  **/
glm::vec3 GameResources::playerpos = glm::vec3(0.0f, 0.0f, 0.0f);

/**  getPlayerPos()  **/
glm::vec3 GameResources::getPlayerPos() {
    return playerpos;
}

/**  setPlayerPos() **/
void GameResources::setPlayerPos(const glm::vec3& pos) {
    playerpos = pos;
}



/**  View and Projection Matrices initialization  **/
//  Identity matrix
glm::mat4 GameResources::view = glm::mat4(1.0f);
//  Identity matrix
glm::mat4 GameResources::projection = glm::mat4(1.0f);

/**  setViewMatrix() **/
void GameResources::setViewMatrix(glm::mat4 matrix) {
    view = matrix;
}

/**  setProjectionMatrix()  **/
void GameResources::setProjectionMatrix(glm::mat4 matrix) {
    projection = matrix;
}

/**  getViewMatrix()  **/
glm::mat4 GameResources::getViewMatrix() {
    return view;
}

/**  getProjectionMatrix()  **/
glm::mat4 GameResources::getProjectionMatrix() {
    return projection;
}

/**  initialize object map  **/
std::map<std::string, game::Model> GameResources::objects;

/**  loadModel() **/
game::Model GameResources::loadModel(const std::string& filename, const std::string& name) {
    //  Search to see if desired model is already in the map
    auto it = std::find_if(objects.begin(), objects.end(),
                           [&name](const std::pair<std::string, game::Model>& p) {return name == p.first;});

    //  If object found then return it
    if (it != objects.end()) {
        return (*it).second;

    //  Else initialize the model
    } else {
        game::Model object;
        object.init(filename);
        objects[name] = object;
        return objects[name];
    }
}




/**  destroy()  **/
void GameResources::destroy() {
    //  If cube was initialized then delete the allocated memory
    if (cube_init) {
        glDeleteVertexArrays(1, &cube.vao);
        glDeleteBuffers(1, &cube.vbo);
    }

    if (cube2_init) {
        glDeleteVertexArrays(1, &cube2.vao);
        glDeleteBuffers(1, &cube2.vbo);
    }

    //  delete shaders
    for (auto it = shaders.begin(); it != shaders.end(); ++it) {
        (*it).second.deleteShader();
    }

    //  delete objects
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        (*it).second.destroyModel();
    }

    //  delete textures
    if (textures_init) {
        textures.deleteTextures();
    }

    //  delete tile
    if (tile_init) {
        glDeleteVertexArrays(1, &tile.vao);
        glDeleteBuffers(1, &tile.vbo);
        glDeleteBuffers(1, &tile.ebo);
    }

    if (tile2_init) {
        glDeleteBuffers(1, &tile2.ebo);
        glDeleteBuffers(1, &tile2.vbo);
        glDeleteVertexArrays(1, &tile2.vao);
    }
}


