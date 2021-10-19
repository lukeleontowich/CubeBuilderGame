/****************************************************
** Project: Cube Builder Game
** File: CitySlabDecorator.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implements the CitySlabDecorator
*******************************************************/


#include "CitySlabDecorator.h"

/**  Constructor  **/
/** Takes a slab pointer and copies the contents of the local slap map of the
** incoming slab. The incoming pointer is deleted here so it is important
** to input a new slab not an existing one
** City slabs when created are meant to be a fresh start
*/
CitySlabDecorator::CitySlabDecorator(Slab* slab) {

    auto map_ref = slab->getLocalSlabMap();

    //  Copy slab_map information from incoming slab
    for (unsigned i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        this->local_slab_map[i] = map_ref[i];
    }

    //  Release slab
    delete slab;

    //  Draw Road through middle
    for (unsigned i = SLAB_SIZE / 2 -1; i <= SLAB_SIZE / 2; ++i) {
        for (unsigned j = 0; j < SLAB_SIZE; ++j) {
            this->local_slab_map[i*SLAB_SIZE + j] = game::ROAD;
        }
    }
    //  Draw intersecting road
    for (unsigned j = SLAB_SIZE / 2 - 1; j <= SLAB_SIZE / 2; ++j) {
        for (unsigned i = 0; i < SLAB_SIZE; ++i) {
            this->local_slab_map[i*SLAB_SIZE + j] = game::ROAD;
        }
    }
    //  Draw road around parameter
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        int j = 0;
        this->local_slab_map[i*SLAB_SIZE + j] = game::ROAD;
    }
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        int j = SLAB_SIZE-1;
        this->local_slab_map[i*SLAB_SIZE + j] = game::ROAD;
    }
    for (unsigned j = 0; j < SLAB_SIZE; ++j) {
        int i = 0;
        this->local_slab_map[i*SLAB_SIZE + j] = game::ROAD;
    }
    for (unsigned j = 0; j < SLAB_SIZE; ++j) {
        int i = SLAB_SIZE - 1;
        this->local_slab_map[i*SLAB_SIZE + j] = game::ROAD;
    }

    //  Initialize the collision map
    this->initCollisionMap();
}

/** Destructor  **/
CitySlabDecorator::~CitySlabDecorator() {}

