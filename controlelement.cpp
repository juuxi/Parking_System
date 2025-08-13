#include "controlelement.h"

ControlElement::ControlElement() {
    is_opened = false;
}

void ControlElement::open() {
    is_opened = true;
}

void ControlElement::close() {
    is_opened = false;
}
