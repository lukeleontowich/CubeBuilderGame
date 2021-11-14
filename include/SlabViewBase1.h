/*****************************************************
** Project: Cube Builder Game
** File: SlabViewBase1.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: SubClass of SlabView, Implements methods
** That will be inherited by other concrete classes
*****************************************************/

#ifndef SLABVIEWBASE1_H
#define SLABVIEWBASE1_H

#include <SlabView.h>


class SlabViewBase1 : public SlabView {
public:
    /** Constructor  **/
    SlabViewBase1();

    /**  Desctructor  **/
    virtual ~SlabViewBase1();

    /** draw()
    ** @param int, int, Slab*
    ** @return void
    ** Description: Draw must be implemented in concrete classes
    **/
    virtual void draw(int world_map_x, int world_map_z, Slab* slab) = 0;

    /** drawScenery()
    ** @param int, int, Slab*
    ** @return none
    ** Description: Draws the 3D objects (aside from the cubes). Implemented
    ** in concrete classes
    **/
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab) = 0;

    /** drawTiles()
    ** @param int, int, Slab*
    ** @return void
    ** Description: Implements method of drawing tiles
    **/
    virtual void drawTiles(int world_map_x, int world_map_z, Slab* slab);

    /** drawCubes()
    ** @param int, int, Slab*
    ** @return void
    ** Descriptions: Implements cube drawing method
    **/
    virtual void drawCubes(int world_map_x, int world_map_z, Slab* slab);

    /** setBrightness()
    ** @param Shader& shader.
    ** @return void
    ** Description: Set the brightness in the shader
    **/
    virtual void setBrightness(game::Shader& shader);
};

#endif // SLABVIEWBASE1_H
