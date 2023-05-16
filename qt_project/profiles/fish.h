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
    //Fish constructors
    Fish();
    Fish(int id, Profile *owner, QString name,int age, QString location, QString species, QDateTime dateCreated, QString description);
    Fish(std::map<QString, QString> fishData);

    //Fish deconstructor
    ~Fish();

    //Edit information for fish
    void edit_data(QString name, int age, QString location, QString species, QString description);
    void edit_picture(QByteArray picture);
    //Detect fish owner
    bool is_owner(Profile *profile);

    //Getter methods
    int get_id();
    int get_ownerId();
    QString get_name();
    int get_age();
    QString get_location();
    QString get_species();
    QDateTime get_dateCreated();
    QString get_description();
    QByteArray get_picture();
    Profile *get_owner();

private:
    int fishId;
    int ownerId;
    QString name;
    int age;
    QString location;
    QString species;
    QDateTime dateCreated;
    QString description;
    QByteArray picture;

    Profile *owner;

};

#endif // FISH_H
