/**********************************************************
** Project: Cube Builder Game
** File: GrassSlab.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Concrete slab class containing grass land
*********************************************************/

#ifndef GRASSSLAB_H
#define GRASSSLAB_H

#include "Slab.h"
#include "TempSlabView.h"
#include "GrassSlabView1.h"

class GrassSlab : public Slab {
public:
    GrassSlab();
    ~GrassSlab();
};

#endif // GRASSSLAB_H
