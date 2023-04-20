#ifndef DATABASE_H
#define DATABASE_H

#include "QString"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QVariant"
#include "QSqlRecord"
#include <string>
#include <iostream>

class Database
{
public:
    Database();
    ~Database();

    void open();
    void query_exec(QString);
    int query_size();
    QString query_string();
    void close();

private:
    QSqlDatabase db;
    QSqlQuery    *query;
};

#endif // DATABASE_H
