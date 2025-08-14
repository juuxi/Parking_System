#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "trafficlight.h"
#include "barrier.h"
#include "ticket.h"
#include "level.h"

class Widget : public QWidget
{
    Q_OBJECT

    TrafficLight tl;
    Barrier br;
public:
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ~Widget();
};
#endif // WIDGET_H
