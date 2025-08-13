#ifndef BARRIER_H
#define BARRIER_H

#include "controlelement.h"

class Barrier : public ControlElement
{
public:
    Barrier();
    void draw(QPainter *);
};

#endif // BARRIER_H
