#include "vehicle.h"

Vehicle::Vehicle(): enter_time(QTime(QDateTime::currentDateTime().time())), duration(QTime()),
    is_placed_correctly(true) {}

void Vehicle::updateDuration() {
    int secs = enter_time.hour() * 3600;
    secs += enter_time.minute() * 60;
    secs += enter_time.second();
    duration = QTime(QDateTime::currentDateTime().time()).addSecs(-secs);
}

QString Vehicle::getPlate() const {
    return plate;
}

QString Vehicle::getModel() const {
    return model;
}

QTime Vehicle::getEnterTime() const {
    return enter_time;
}

QTime Vehicle::getDuration() const {
    return duration;
}

bool Vehicle::getIsPlacedCorrectly() const {
    return is_placed_correctly;
}

bool Vehicle::operator==(const Vehicle& other) const {
    if (this->plate != other.plate) {
        return false;
    }
    return true;
}
