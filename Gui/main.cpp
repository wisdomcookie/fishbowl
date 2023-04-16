#include "home.h"
#include "connect.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Home w;
    Connect c;
    w.show();
    return a.exec();
}
