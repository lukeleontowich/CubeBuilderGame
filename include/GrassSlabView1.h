/*****************************************************
** Project: Ultimate Mayor
** File: GrassSlabView1.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: **
** Implements the drawing method for a GrassSlab
*****************************************************/

#ifndef GRASSSLABVIEW1_H
#define GRASSSLABVIEW1_H

#include "GameResources.h"
#include "SlabViewBase1.h"
#include <cstdlib>

class GrassSlabView1 : public SlabViewBase1 {
private:
    //  Defines how much grass to draw
    unsigned int grass_density;

    //  Describes where each chunk of grass goes on the slab
    unsigned int grass_array[SLAB_SIZE*SLAB_SIZE];

    /** initGrassArray()
    ** @param none
    ** @return void
    ** Description:
    ** initializes a random grass seed
    **/
    void initGrassArray();

    /** generateRandomNumber()
    ** @param none
    ** @return unsigned int: a random number
    ** Desciption:
    ** generates a random number from 0 - grass_density
    **/
    unsigned int generateRandomNumber();

public:
    /** Constructor  **/
    GrassSlabView1();

    /** Destructor  **/
    virtual ~GrassSlabView1();

    /** draw()
    ** @param int, int, Slab*:
    ** the world_map location refers to which slab on the world map we
    ** are currently on. The Slab pointer contains the information of
    ** the slab
    ** @return void
    ** Description:
    ** Implements how to draw a grass slab
    **/
    virtual void draw(int world_map_x, int world_map_z, Slab* slab);

    /** drawGrassModels()
    ** @param int, int, Slab*:
    ** the world_map location refers to which slab on the world map we
    ** are currently on. The Slab pointer contains the information of
    ** the slab
    ** @return void
    ** Description:
    ** Draws the 3D grass
    **/
    void drawGrassModels(int world_map, int world_map_z, Slab* slab);

    /** drawScenery
    ** @param int, int, Slab*:
    ** the world_map location refers to which slab on the world map we
    ** are currently on. The Slab pointer contains the information of
    ** the slab
    ** @return void
    ** Description:
    ** Implements how to draw the 3D scenery. Model drawing.
    **/
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab);
};

#endif // GRASSSLABVIEW1_H
