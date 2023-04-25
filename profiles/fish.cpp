#include "fish.h"

Fish::Fish() {

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
