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
    void close();

    void query_exec(QString);

    //Maps contain field:value pairs
    std::vector<std::map<QString, QString>> query_select(QString table, std::vector<QString> fields);
    int query_size();
    QString query_string();
    std::vector<std::map<QString, QString>> query_vector();

private:
    QSqlDatabase db;
    QSqlQuery    *query;
    //std::vector<std::map<QString, QString>> queryVector;
};

#endif // DATABASE_H
