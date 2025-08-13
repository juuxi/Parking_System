#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);
}

Widget::~Widget() {}
