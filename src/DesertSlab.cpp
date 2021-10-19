/*****************************************************
** Project: Cube Builder Game
** File: DesertSlab.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: This class implements DesertSlab
*****************************************************/

#include "DesertSlab.h"

#include "GrassSlabView1.h"
/** Constructor  **/
DesertSlab::DesertSlab() {
    //  Set default height
    _height = 2;

    //  File the ground with desert
    std::fill(local_slab_map,
              local_slab_map + SLAB_SIZE*SLAB_SIZE,
              game::DESERT);

    //  Initialize the collision map
    this->initCollisionMap();

    /** CHANGE WHEN DesertSlabView is finished **/
    view = new GrassSlabView1;
}

/** Destructor **/
DesertSlab::~DesertSlab() {}



