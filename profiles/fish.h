#ifndef FISH_H
#define FISH_H
#include "qdatetime.h"
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
    Fish(int id, Profile *owner, QString name,int age, QString location, QString species, QString description);
    Fish(std::map<QString, QString> fishData);
    ~Fish();

    //Fish sub-profile information
//    string name, location, species, bio;
//    Profile* owner;
    int get_id();
    QDateTime get_dateCreated();

private:
    int fishId;
    int ownerId;
    QString name;
    int age;
    QString location;
    QString species;
    QDateTime dateCreated;
    QString description;

    Profile *owner;

};

#endif // FISH_H
