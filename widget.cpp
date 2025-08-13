#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    tl.draw(&p);
    br.draw(&p);
    p.end();
}

Widget::~Widget() {}
