/*****************************************************
** Project: Cube Builder Game
** File: Hand.h
** Author: Luke Leontowich
** Date: Novemeber 12, 2021
** Description: Class that handles the cube that is in
** the player's hand
*****************************************************/


#ifndef HAND_H
#define HAND_H

#include "Texture.h"
#include "Texture2D.h"
#include "GameResources.h"

class Hand {
private:
    //  The current texture of the block in the player's hand
    game::TEXTURE_TYPE _current_texture;

    //  If the block is in hand or hidden
    bool _block_in_hand = true;

public:
    /**  Constructor  **/
    Hand();

    /** Destructor  **/
    ~Hand();

    /** changeTexture()
    ** @param texture to be in player's hand
    ** @return void
    ** Description: Changes the current texture in the player's hand to a new one
    **/
    void changeTexture(game::TEXTURE_TYPE texture);

    /**
    ** @param bool state: new state for _block_in_hand
    ** @return void
    ** Description: Changes the _block_in_hand state
    **/
    void changeBlockInHand(bool state);

    /** draw()
    ** @param vec3 shift, shift to where we want to draw the block
    ** @return void
    ** Description: draws the block with the current texture'
    **/
    void draw(const glm::vec3& shift);

    /** Getters  **/
    bool block_in_hand();
    game::TEXTURE_TYPE current_texture();
};

#endif // HAND_H
