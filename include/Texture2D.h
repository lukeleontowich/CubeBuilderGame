#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Texture.h"

namespace game {

class Texture2D {
public:
    Texture2D();
    ~Texture2D();
    game::TEXTURE_ERROR init();
    bool bind(unsigned int index);
    void deleteTextures();

private:
    unsigned int textures[game::NUM_TEXTURES];
    bool addTexture(unsigned int index, std::string file_path);

};

}
#endif // TEXTURE2D_H
