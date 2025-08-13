#include "trafficlight.h"

TrafficLight::TrafficLight() {}

void TrafficLight::draw(QPainter* p) {
    p->drawRect(100, 100, 500, 300);
}
