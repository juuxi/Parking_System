#include "barrier.h"

Barrier::Barrier() : ControlElement(BARRIER) {}

void Barrier::draw(QPainter* p) {
    p->drawEllipse(500, 500, 150, 100);
}
