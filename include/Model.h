#ifndef MODEL_H
#define MODEL_H


#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"

namespace game {

class Model {
public:
    Model();
    ~Model();

    void draw(Shader& shader);
    void destroyModel();
    void init(const std::string& path);

private:
    std::vector<game::TextureData> textures_loaded;
    std::vector<game::Mesh> meshes;
    std::string directory;


    void processNode(aiNode* node, const aiScene* scene);
    game::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<game::TextureData> loadMaterialTextures(aiMaterial* mat,
                                                        aiTextureType type,
                                                        std::string type_name);
    unsigned int textureFromFile(const char* path);

};

}
#endif // MODEL_H
