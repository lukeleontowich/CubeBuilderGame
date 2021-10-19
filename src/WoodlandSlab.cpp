/*****************************************************
** Project: Cube Builder Game
** File: WoodlandSlab.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of WoodlandSlab.cpp
*****************************************************/

#include "WoodlandSlab.h"

WoodlandSlab::WoodlandSlab() {
    std::fill(local_slab_map, local_slab_map + SLAB_SIZE*SLAB_SIZE, game::WOODLAND);
    _height = 2;
    this->initCollisionMap();
    view = new WoodlandSlabView1;
}

WoodlandSlab::~WoodlandSlab() {
    if (view != nullptr) {
        delete view;
        view = nullptr;
    }
}
