#ifndef LEVEL_H
#define LEVEL_H

#include "vehicle.h"
#include "trafficlight.h"
#include "barrier.h"
#include <QVector>
#include <QSharedPointer>
#include <algorithm>

class Level
{
    int serial_number;
    QVector<QVector<Vehicle>> lines;
    QVector<QSharedPointer<ControlElement>> control_elements;
    bool is_opened;

public:
    Level();
    Level(int);

    void add_vehicle(Vehicle, int, int);
    void remove_vehicle(Vehicle);
    void add_control_element(QSharedPointer<ControlElement>&);
    void remove_control_element(QSharedPointer<ControlElement>&);
};

#endif // LEVEL_H
