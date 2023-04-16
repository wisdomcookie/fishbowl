#include "connect.h"

Connect::Connect() {
    h = new Home();

    s.addWidget(h);

    s.setCurrentWidget(h);
    s.showMaximized();
}
