#include "trafficlight.h"

TrafficLight::TrafficLight() : ControlElement(TRAFFIC_LIGHT) {}

void TrafficLight::draw(QPainter* p) {
    p->drawRect(100, 100, 500, 300);
}
