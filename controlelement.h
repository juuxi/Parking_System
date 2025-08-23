#ifndef CONTROLELEMENT_H
#define CONTROLELEMENT_H

#include <QPainter>

enum ConctrolElementType {
    TRAFFIC_LIGHT = 0,
    BARRIER = 1
};

class ControlElement
{
    bool is_opened;
public:
    int type;
    ControlElement();
    ControlElement(int);
    void open();
    void close();
    bool get_is_opened();
    virtual void draw(QPainter *) = 0;
};

#endif // CONTROLELEMENT_H
