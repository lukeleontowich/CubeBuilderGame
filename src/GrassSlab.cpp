/*****************************************************
** Project: Ultimate Mayor
** File: GrassSlab.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of GrassSlab class
*****************************************************/

#include "GrassSlab.h"

/**  Constructor  **/
GrassSlab::GrassSlab() {
    //  Fill the local_slab_map with all grass
    std::fill(local_slab_map,
              local_slab_map + SLAB_SIZE*SLAB_SIZE,
              game::GRASS);
    //  Default height
    _height = 2;

    //  Initialize collision map
    this->initCollisionMap();

    //  Set the view
    view = new GrassSlabView1;
}

/**  Destructor  **/
GrassSlab::~GrassSlab() {
    //  delete the view
    if (view != nullptr) {
        delete view;
        view = nullptr;
    }
}
