#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "controlelement.h"

class TrafficLight : public ControlElement
{
public:
    TrafficLight();
    void draw(QPainter *);
};

#endif // TRAFFICLIGHT_H
