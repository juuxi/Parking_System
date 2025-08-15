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
    bool check_login(QString, QString);
};

#endif // DATABASE_H
