#ifndef FISH_H
#define FISH_H
#include <map>
#include <string>
#include <QString>
using namespace std;

class Profile;
//#include "profile.h"

class Fish
{
public:
    Fish();
    Fish(string name, string species);
    Fish(std::map<QString, QString> fishData);
    ~Fish();

    //Fish sub-profile information
    string name, location, species, bio;
    Profile* owner;

private:
    int fishId;
    //QString name;
    int ownerId;

};

#endif // FISH_H
