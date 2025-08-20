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
    QString getPlate() const;
    QString getModel() const;
    QTime getEnterTime() const;
    QTime getDuration() const;
    bool getIsPlacedCorrectly() const;
    bool operator==(const Vehicle&) const;
};

#endif // VEHICLE_H
