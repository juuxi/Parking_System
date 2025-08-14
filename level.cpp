#include "level.h"

Level::Level() : serial_number(0), vehicles(nullptr), control_elements(nullptr), is_opened(true) {}

Level::Level(int num) : serial_number(num), vehicles(nullptr), control_elements(nullptr), is_opened(true) {}
