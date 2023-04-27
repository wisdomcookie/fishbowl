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
    //void query_insert(QString table, std::vector<QString> fields, std::vector<QString> values);
    void query_insert(QString table, std::vector<QString> fields, std::vector<QVariant> values);
    void query_update_by_rowid(QString table, int id, std::vector<QString> fields, std::vector<QVariant> values);
    void query_delete_by_rowid(QString table, int id);
    int get_next_id(QString table);

    int query_size();
    QString query_string();
    std::vector<std::map<QString, QString>> query_vector();

private:
    QSqlDatabase db;
    QSqlQuery    *query;
    //std::vector<std::map<QString, QString>> queryVector;
};

#endif // DATABASE_H
