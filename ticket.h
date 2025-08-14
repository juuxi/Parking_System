#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include "vehicle.h"

struct Ticket
{
    QString number;
    Vehicle v;
    Ticket(QString _number, Vehicle _v) : number(_number), v(_v) {}
};

#endif // TICKET_H
