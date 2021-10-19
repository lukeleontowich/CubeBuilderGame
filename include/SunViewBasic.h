/*****************************************************
** Project: Cube Builder Game
** File: SunViewBasic.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Concrete class that draws a basic
** cube version of the Sun
*****************************************************/

#ifndef SUNVIEWBASIC_H
#define SUNVIEWBASIC_H

#include <SunView.h>

#include "GameResources.h"

class SunViewBasic : public SunView {
public:
    /** Constructor  **/
    SunViewBasic();

    /** Destructor  **/
    virtual ~SunViewBasic();

    /** draw()
    ** @param Sun*
    ** @return void
    ** Description: Draws a basic cube version of the sun
    **/
    virtual void draw(Sun* sun);
};

#endif // SUNVIEWBASIC_H
