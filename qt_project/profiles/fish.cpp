#include "fish.h"
#include "../profiles/profile.h"

Fish::Fish() {

}

Fish::Fish(int id, Profile *owner, QString name, int age, QString location, QString species, QDateTime dateCreated, QString description):
    fishId(id), ownerId(owner->get_id()), name(name), age(age), location(location), species(species), dateCreated(dateCreated), description(description), owner(owner){

}
Fish::Fish(std::map<QString, QString> fishData){
    fishId = fishData[QString("fish_id")].toInt();
    ownerId = fishData[QString("owner_id")].toInt();
    name = fishData[QString("name")];
    age = fishData[QString("age")].toInt();
    location = fishData[QString("location")];
    species = fishData[QString("species")];

    QString dateString = fishData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    description = fishData[QString("description")];
}


Fish::~Fish() {

}


void Fish::edit_data(QString name, int age, QString location, QString species, QString description){
    this->name = name;
    this->age = age;
    this->location = location;
    this->species = species;
    this->description = description;
}

void Fish::edit_picture(QByteArray picture){
    this->picture = picture;
}

bool Fish::is_owner(Profile *profile){
    return profile == owner;
}

int Fish::get_id(){
    return fishId;
}
int Fish::get_ownerId(){
    return ownerId;
}
QString Fish::get_name(){
    return name;
}
int Fish::get_age(){
    return age;
}
QString Fish::get_location(){
    return location;
}
QString Fish::get_species(){
    return species;
}
QDateTime Fish::get_dateCreated(){
    return dateCreated;
}
QString Fish::get_description(){
    return description;
}
QByteArray Fish::get_picture(){
    return picture;
}

Profile *Fish::get_owner(){
    return owner;
}
