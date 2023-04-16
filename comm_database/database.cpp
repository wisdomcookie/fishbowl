#include "database.h"

database::database()
{
    QString path("../database_info/fishbowl.sqlite");

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(path);
}

database::~database(){

}

void database::open(){
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

int database::queries(QString s) {

    // create the sql command
    QString sqlcmd = s;

    // execute the provided sql call
    if(query->exec(sqlcmd) == false) {
        QSqlError err = query->lastError();
        qDebug() << err.text();
    }

    // return the number of rows retrieved from the table
    return query->size();
}

//int database::insert()

void database::close(){
    db.close();

    std::cout  << "Database: successfully closed"
               << std::endl;
}
