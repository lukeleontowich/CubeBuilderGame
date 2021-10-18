#ifndef SUNVIEWBASIC_H
#define SUNVIEWBASIC_H

#include <SunView.h>

#include "GameResources.h"

class SunViewBasic : public SunView {
public:
    SunViewBasic();
    virtual ~SunViewBasic();
    virtual void draw(Sun* sun);
};

#endif // SUNVIEWBASIC_H
