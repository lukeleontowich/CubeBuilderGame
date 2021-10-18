#include "Object.h"
/*
Object::Object(const std::string& file) {
    _filename = file;
}

Object::~Object() {
    //dtor
}

bool Object::init() {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(_filename, aiProcess_Triangulate || aiProcess_GenNormals);

    //  Check if loaded
    if (!scene) {
        std::cout << "Assimp file ";
        std::cout << _filename << " not loaded\n";
        return false;
    }
    aiMesh* mesh = scene->mMeshes[0];

    if (!mesh) {
        std::cout << _filename << " mesh not loaded\n";
        return false;
    }

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        glm::vec3 temp;
        Vertex vertex;

        //  Get position
        temp.x = mesh->mVertices[i].x;
        temp.y = mesh->mVertices[i].y;
        temp.z = mesh->mVertices[i].z;
        vertex.pos = temp;

        //  Get Normals
        if (!mesh->HasNormals()) {
            std::cout << _filename << " normal's not found\n";
        } else {
            temp.x = mesh->mNormals[i].x;
            temp.y = mesh->mNormals[i].y;
            temp.z = mesh->mNormals[i].z;
            vertex.normal = temp;
        }

        //  Get Colors
        glm::vec4 temp_color;
        temp_color.x = mesh->mColors[i][0];


    }

    return true;
}
*/
