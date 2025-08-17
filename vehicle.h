#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>
#include <QTime>

class Vehicle
{
    QString plate;
    QString model;
    QTime enter_time;
    QTime duration;
    bool is_placed_correctly;

public:
    Vehicle();
    void updateDuration();
    bool operator==(const Vehicle&) const;
};

#endif // VEHICLE_H
