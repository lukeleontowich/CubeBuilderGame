/*****************************************************
** Project: Cube Builder Game
** File: WoodlandSlabView1.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implements methods to draw a woodland
** slab
*****************************************************/
#ifndef WOODLANDSLABVIEW1_H
#define WOODLANDSLABVIEW1_H

#include "GameResources.h"
#include "SlabViewBase1.h"

class WoodlandSlabView1 : public SlabViewBase1 {
public:
    /**  Constructor  **/
    WoodlandSlabView1();

    /**  Destructor  **/
    virtual ~WoodlandSlabView1();

    /** draw()
    ** @param int, int, Slab*
    ** @return void
    ** Description: Implements method to draw woodland slab
    **/
    virtual void draw(int world_map_x, int world_map_z, Slab* slab);

    /** drawTreeModels()
    ** @param int, int, Slab*
    ** @return void
    ** Description: Method to draw 3D trees
    **/
    void drawTreeModels(int world_map, int world_map_z, Slab* slab);

    /** drawScenery()
    ** @param int, int, Slab*
    ** @return void
    ** Description: Implements method to draw 3D scenery
    **/
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab);
};

#endif // WOODLANDSLABVIEW1_H
