#include <iostream>
#include "database.h"

using namespace std;

int main()
{
    Database d;
    d.open();

    d.query_exec("select * from profiles;");
    cout << d.query_size() << endl;
    cout << d.query_string();
    d.close();
}
