/*****************************************************
** Project: Cube Builder Game
** File: TempSlabView.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Basic slab viewing class
*****************************************************/
#ifndef TEMPSLABVIEW_H
#define TEMPSLABVIEW_H

#include <SlabView.h>


class TempSlabView : public SlabView {
public:
    TempSlabView();
    virtual ~TempSlabView();

    //  implement
    virtual void draw(int world_map_x, int world_map_z, Slab* slab);
    virtual void drawScenery(int world_map_x, int world_map_z, Slab* slab);
};

#endif // TEMPSLABVIEW_H
