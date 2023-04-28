#include <iostream>
#include "database.h"
#include "QDateTime"
using namespace std;

int main()
{
    Database d;
    d.open();

    d.query_exec("select * from profiles;");
    cout << d.query_size() << endl;
    cout << d.query_string().toStdString() << endl;

    d.query_exec("insert into profiles(username, name, type, date_created) values('nathandinh2', 'Nathan', 'user', date());");
    d.query_exec("select * from profiles;");
    cout << d.query_string().toStdString() << endl;

    QString str = QDateTime::currentDateTimeUtc().toString();
    d.query_exec("update profiles set(name, description, date_created) = ('Nathan2', 'check', '" + str + "') where username='nathandinh2';");
    d.query_exec("select * from profiles;");
    cout << d.query_string().toStdString() << endl;

    d.query_exec("delete from profiles where username='nathandinh2';");
    d.query_exec("select * from profiles;");
    cout << d.query_string().toStdString() << endl;


    std::vector<QString> fields = {QString("profile_id"), QString("username")};

    std::vector<std::map<QString, QString>> res = d.query_select(QString("profiles"), fields);
    cout << d.query_string().toStdString() << endl;

    d.close();

    cout << QDateTime::currentDateTimeUtc().toString(QString("yyyy-MM-dd hh:mm:ss")).toStdString() << endl;

    QString str1("asd");
    QString str2("gsdf");

    cout << str1.toStdString();
    cout << str2.toStdString();

    str1 = str2;


    cout << str1.toStdString();
    cout << str2.toStdString();
    cout << d.query_size();
    cout << 0;
    return 0;

}
