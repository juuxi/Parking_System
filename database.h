#ifndef DATABASE_H
#define DATABASE_H

#include "pgconnection.h"
#include <QString>
#include <fstream>

class DataBase
{
    PGConnection pg;
public:
    DataBase();
};

#endif // DATABASE_H
