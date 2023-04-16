#ifndef CONNECT_H
#define CONNECT_H
#include "home.h"
#include <QObject>
#include <QStackedWidget>

class Connect : public QObject {

    Q_OBJECT

public:
    Connect();
    Home* h;

private:
    QStackedWidget s;
};

#endif // CONNECT_H
