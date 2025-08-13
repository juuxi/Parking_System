#ifndef CONTROLELEMENT_H
#define CONTROLELEMENT_H

#include <QPainter>

class ControlElement : QPainter
{
    bool is_opened;
public:
    ControlElement();
    void open();
    void close();
    virtual void draw(QPainter*) = 0;
};

#endif // CONTROLELEMENT_H
