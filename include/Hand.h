#ifndef HAND_H
#define HAND_H

#include "Texture.h"
#include "Texture2D.h"
#include "GameResources.h"

class Hand {
private:
    game::TEXTURE_TYPE _current_texture;
    bool _block_in_hand;
public:
    Hand();
    ~Hand();
    void changeTexture(game::TEXTURE_TYPE texture);
    void changeBlockInHand(bool state);
    void draw(const glm::vec3& shift);
    bool block_in_hand();
    game::TEXTURE_TYPE current_texture();
};

#endif // HAND_H
