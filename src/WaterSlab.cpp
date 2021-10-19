/*****************************************************
** Project: Cube Builder Game
** File: WaterSlab.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of WaterSlab.h
*****************************************************/

#include "WaterSlab.h"
#include "GrassSlabView1.h"
WaterSlab::WaterSlab() {
    _height = 1;

    std::fill(local_slab_map,
              local_slab_map + SLAB_SIZE*SLAB_SIZE,
              game::WATER);
    this->initCollisionMap();

    /** CHANGE WHEN WaterSlabView is finished **/
    view = new GrassSlabView1;
}

WaterSlab::~WaterSlab() {}

