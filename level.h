#ifndef LEVEL_H
#define LEVEL_H

#include "vehicle.h"
#include "controlelement.h"

class Level
{
    int serial_number;
    Vehicle* vehicles;
    ControlElement* control_elements;
    bool is_opened;

public:
    Level();
    Level(int);
};

#endif // LEVEL_H
