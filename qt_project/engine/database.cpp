﻿#include "database.h"

Database::Database()
{
    QString path("../../database_info/fishbowlDB.sqlite");

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(path);

    if (!db.open())
    {
        std::cout << "Error: connection with database fail"
                  << std::endl;
        exit(1);
    }
    else
    {
        std::cout  << "Database: connection ok"
                  << std::endl;
    }

    query = new QSqlQuery(db);
}

Database::~Database(){
    delete query;
}


void Database::open(){
    if (!db.open())
    {
       std::cout << "Error: connection with database fail"
                 << std::endl;
       exit(1);
    }
    else
    {
       std::cout  << "Database: connection ok"
                  << std::endl;
    }

    query = new QSqlQuery(db);
}

void Database::query_exec(QString s) {

    // create the sql command
    QString sqlcmd = s;

    // execute the provided sql call
    if(query->exec(sqlcmd) == false) {
        std::cout << s.toStdString();
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }

    // return the number of rows retrieved from the table

}

std::vector<std::map<QString, QString>> Database::query_select(QString table, std::vector<QString> fields){
    QString fieldstring = fields[0];

    for(int i = 1; i < fields.size(); i++){
        fieldstring += "," + fields[i];
    }

    QString sqlcmd = QString("select " + fieldstring + " from " + table + ";");

    if(query->exec(sqlcmd) == false) {
        std::cout << sqlcmd.toStdString();
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }

    std::vector<std::map<QString, QString>> res;

    while(query->next()){
        std::map<QString, QString> row;
        for(QString &field: fields){
            row[field] = query->value(field).toString();
        }
        res.push_back(row);
    }
    return res;

}

void Database::query_insert(QString table, std::vector<QString> fields, std::vector<QVariant> values){

    QString fieldstring = fields[0];
    QString valuePlaceholders = QString(":" + fields[0]);

    for(int i = 1; i < fields.size(); i++){
        fieldstring += "," + fields[i];
        valuePlaceholders += ", :" + fields[i];
    }

    QString debug("insert into " + table + " (" + fieldstring + ") values (" + valuePlaceholders + ")");

    query->prepare("insert into " + table + " (" + fieldstring + ") values (" + valuePlaceholders + ")");

    for(int i = 0; i < fields.size(); i++){
        query->bindValue(i, values[i]);
    }

    if(query->exec() == false) {
        std::cout << debug.toStdString();
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
//    query->exec();
}

void Database::query_update_by_rowid(QString table, int id, std::vector<QString> fields, std::vector<QVariant> values){

    QString fieldstring = fields[0];
    QString valuePlaceholders = QString(":" + fields[0]);

    for(int i = 1; i < fields.size(); i++){
        fieldstring += "," + fields[i];
        valuePlaceholders += ", :" + fields[i];
    }

    QString debug("update " + table + " set(" + fieldstring + ") = (" + valuePlaceholders + ") where rowid=:rowid");
    query->prepare("update " + table + " set(" + fieldstring + ") = (" + valuePlaceholders + ") where rowid=:rowid");

    for(int i = 0; i < fields.size(); i++){
        query->bindValue(i, values[i]);
    }
    query->bindValue(":rowid", id);

    if(query->exec() == false) {

        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

void Database::query_delete_by_rowid(QString table, int id){

    query->prepare("delete from " + table + " where rowid = :rowid");
    query->bindValue(":rowid", id);

    if(query->exec() == false) {

        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

QByteArray Database::load_fish_picture(int fishId){
    query->prepare("select fish_img from fish where fish_id=:id");
    query->bindValue(":id", fishId);
    if(query->exec() == false) {

        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
    query->next();
    return query->value(0).toByteArray();
}


void Database::save_fish_picture(int fishId, QByteArray fishPicture){

    query->prepare("update fish set fish_img=:picture where fish_id=:id");
    query->bindValue(":picture", fishPicture);
    query->bindValue(":id", fishId);
    if(query->exec() == false) {

        QSqlError err = query->lastError();
        qDebug() << err.text();
    }
}

int Database::get_next_id(QString table){

    QString sqlcmd = QString("select max(rowid) from " + table + ";");
    query_exec(sqlcmd);
    query->next();
    return query->value(0).toInt() + 1;
}

int Database::query_size(){
    int res = 0;
    if(query->last())
    {
        res =  query->at() + 1;
        query->first();
        query->previous();
    }
    return res;
}


QString Database::query_string(){

    QString str("");
    query->first();

    std::vector<std::vector<QString>> results;
    do {

        QSqlRecord rec = query->record();
        std::vector<QString> row;
        for(int i = 0; i < rec.count(); i++){
            row.push_back(rec.value(i).toString());
        }
        results.push_back(row);
    } while (query->next());

    for(auto &i: results){
        for(auto &j: i){
            str += j + "|";
        }
        str += "\n";
    }


    return str;

}

std::vector<std::map<QString, QString>> Database::query_vector(){
    std::vector<std::map<QString, QString>> res;

    while(query->next()){
        std::map<QString, QString> row;

    }
}

//int database::insert()

void Database::close(){
    db.close();

    std::cout  << "Database: successfully closed"
               << std::endl;
}
