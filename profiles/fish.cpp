#include "fish.h"
#include "../profiles/profile.h"

Fish::Fish() {

}

Fish::Fish(int id, Profile *owner, QString name,int age, QString location, QString species, QString description):
    fishId(id), ownerId(owner->get_id()), name(name), age(age), location(location), species(species), dateCreated(QDateTime::currentDateTimeUtc()), description(description), owner(owner){

}
Fish::Fish(std::map<QString, QString> fishData){
    fishId = fishData[QString("fish_id")].toInt();
    ownerId = fishData[QString("owner_id")].toInt();

//    QString dateString = groupData[QString("date_created")];
//    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
//    dateCreated = QDateTime::fromString(dateString, dateFormat);

//    description = groupData[QString("description")];
}

Fish::Fish(string name, string species) {
    this->name = name;
    this->species = species;
}

Fish::~Fish() {

}
