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

std::vector<std::map<QString, QString>> Database::query_select(QString table, std::vector<QString> fields){
    QString fieldstring = fields[0];

    for(int i = 1; i < fields.size(); i++){
        fieldstring += "," + fields[i];
    }

    QString sqlcmd = QString("select " + fieldstring + " from " + table + ";");
    query_exec(sqlcmd);

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

int Database::get_next_id(QString table){

    QString sqlcmd = QString("select max(rowid) from " + table + ";");
    query_exec(sqlcmd);
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
