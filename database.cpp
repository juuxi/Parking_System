#include "database.h"

DataBase::DataBase() {
    std::fstream db_info("../../db_info.txt"); //подключение к БД, данные берутся из скрытого для посторонних глаз текстового файла
    std::string db_name;
    std::string db_user;
    std::string db_pass;
    std::getline(db_info, db_name);
    std::getline(db_info, db_user);
    std::getline(db_info, db_pass);
    pg.set_dbname(db_name);
    pg.set_dbuser(db_user);
    pg.set_dbpass(db_pass);
    pg.reconnect();
    db_info.close();
}

bool DataBase::check_login(QString username, QString password) {
    QString query;
    if (pg.res) {
        char query[256];
        sprintf(query, "SELECT * FROM passwords \
            WHERE username='%s' AND password='%s'", username.toStdString().c_str(), password.toStdString().c_str());
        PGresult* result = PQexec(pg.res, query);
        if (PQntuples(result) > 0) {
            return true;
        }
    }
    return false;
}
