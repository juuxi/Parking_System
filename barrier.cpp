#include "barrier.h"

Barrier::Barrier() {}

void Barrier::draw(QPainter* p) {
    p->drawEllipse(500, 500, 150, 100);
}
