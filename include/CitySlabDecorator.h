/*****************************************************
** Project: Ultimate Mayor
** File: CitySlabDecorator
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: This class decorates a regular slab
** This is a version of the slab decorator
** The contents of the local slab map are copied
** and then overwritten with the road tile
** To copy all information of a slab seemed to costly
*****************************************************/

#ifndef CITYSLABDECORATOR_H
#define CITYSLABDECORATOR_H

#include <SlabDecorator.h>


class CitySlabDecorator : public Slab {
public:
    //  Constructor takes in a slab to decorate with a road
    CitySlabDecorator(Slab* s);

    //  Desctructor
    virtual ~CitySlabDecorator();
};

#endif // CITYSLABDECORATOR_H
