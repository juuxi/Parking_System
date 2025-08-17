#ifndef XML_H
#define XML_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QVector>

#include "level.h"

class Xml
{
public:
    Xml();
    void write(QVector<Level>);
};

#endif // XML_H
