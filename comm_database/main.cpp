#include <iostream>
#include "database.h"

using namespace std;

int main()
{
    Database d;
    d.open();

    d.query_exec("select * from profiles;");
    cout << d.query_size() << endl;
    cout << d.query_string() << endl;

    d.query_exec("insert into profiles (username, name, type, date_created) values ('nathandinh2', 'Nathan', 'user', date()) ;");
    d.query_exec("select * from profiles;");
    cout << d.query_string() << endl;

    d.query_exec("delete from profiles where username='nathandinh2' ;");
    d.query_exec("select * from profiles;");
    cout << d.query_string() << endl;
    d.close();
}
