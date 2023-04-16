#include <iostream>
#include "database.h"

using namespace std;

int main()
{
     database d;
     d.open();

     //d.queries("select * from profile;");
     d.close();
}
