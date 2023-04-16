#ifndef DATABASE_H
#define DATABASE_H

#include "QString"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QVariant"
#include <string>
#include <iostream>

class database
{
public:
    database();
    ~database();

    void open();
    int queries(QString);
    void close();

private:
    QSqlDatabase db;
    QSqlQuery    *query;
};

#endif // DATABASE_H
