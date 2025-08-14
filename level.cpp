#include "level.h"

Level::Level() : serial_number(0), is_opened(true) {}

Level::Level(int num) : serial_number(num), is_opened(true) {}

void Level::add_vehicle(Vehicle v) {
    vehicles.push_back(v);
}

void Level::remove_vehicle(Vehicle v) {
    const auto to_del = std::find(vehicles.begin(), vehicles.end(), v);
    if (to_del != vehicles.end()) {
        vehicles.erase(to_del);
    }
}

void Level::add_control_element(QSharedPointer<ControlElement>& ce) {
    control_elements.push_back(ce);
}

void Level::remove_control_element(QSharedPointer<ControlElement>& ce) {
    const auto to_del = std::find(control_elements.begin(), control_elements.end(), ce);
    if (to_del != control_elements.end()) {
        control_elements.erase(to_del);
    }
}
