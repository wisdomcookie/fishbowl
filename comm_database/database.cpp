#include "database.h"

database::database()
{
    QString path("../ADDAFTERCSVFILES.sqlite");

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
}

void database::close(){
    db.close();

    std::cout  << "Database: successfully closed"
               << std::endl;
}
