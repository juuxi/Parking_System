#include "controlelement.h"

ControlElement::ControlElement() {
    is_opened = false;
}

ControlElement::ControlElement(int _type) : type(_type) {
    is_opened = false;
}

void ControlElement::open() {
    is_opened = true;
}

void ControlElement::close() {
    is_opened = false;
}

bool ControlElement::get_is_opened() {
    return is_opened;
}
