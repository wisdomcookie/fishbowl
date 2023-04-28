#ifndef TEST_H
#define TEST_H
#include <string>
#include <vector>
#include <QString>
#include "../comm_database/database.h"
#include "../engine/engine.h"

class test
{
public:
    test();
    void run();
    Database* d;
    Engine* e;
};

#endif // TEST_H
