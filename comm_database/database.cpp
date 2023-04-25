#include "database.h"

Database::Database()
{
    QString path("../database_info/fishbowlDB.sqlite");

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
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }

    // return the number of rows retrieved from the table

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

    std::vector<std::vector<QString>> results;
    while (query->next()) {

        QSqlRecord rec = query->record();
        std::vector<QString> row;
        for(int i = 0; i < rec.count(); i++){
            row.push_back(rec.value(i).toString());
        }
        results.push_back(row);
    }

    for(auto &i: results){
        for(auto &j: i){
            str += j + "|";
        }
        str += "\n";
    }
    return str;
}

std::vector<std::vector<QString>> Database::query_vector() {

    std::vector<std::vector<QString>> results;
    while (query->next()) {

        QSqlRecord rec = query->record();
        std::vector<QString> row;
        for(int i = 0; i < rec.count(); i++){
            row.push_back(rec.value(i).toString());
        }
        results.push_back(row);
    }
    return results;
}

//int database::insert()

void Database::close(){
    db.close();

    std::cout  << "Database: successfully closed"
               << std::endl;
}
