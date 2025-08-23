#ifndef LEVEL_H
#define LEVEL_H

#include "vehicle.h"
#include "trafficlight.h"
#include "barrier.h"
#include <QVector>
#include <memory>
#include <algorithm>

class Level
{
    int serial_number;
    QVector<std::shared_ptr<ControlElement>> control_elements;
    bool is_opened;

    void drawLine(const QVector<Vehicle>&, int, QPainter*);

public:
    QVector<QVector<Vehicle>> lines;

    Level();
    Level(int);

    void add_vehicle(Vehicle, int, int);
    void remove_vehicle(Vehicle);
    void add_control_element(std::shared_ptr<ControlElement>);
    void remove_control_element(std::shared_ptr<ControlElement>);
    void close();
    void draw(QPainter*);
};

#endif // LEVEL_H
