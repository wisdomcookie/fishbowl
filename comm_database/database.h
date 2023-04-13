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
    void close();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
