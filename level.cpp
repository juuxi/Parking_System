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
