#include "fish.h"
#include "../profiles/profile.h"

/**
 * @brief Empty constructor for fish profiles
 */
Fish::Fish() {

}

/**
 * @brief Constructor for fish utilized by the Engine class to fill in all
 *        important information for a fish, from the database
 * @param id
 * @param owner
 * @param name
 * @param age
 * @param location
 * @param species
 * @param dateCreated
 * @param description
 */
Fish::Fish(int id, Profile *owner, QString name, int age, QString location, QString species, QDateTime dateCreated, QString description):
    fishId(id), ownerId(owner->get_id()), name(name), age(age), location(location), species(species), dateCreated(dateCreated), description(description), owner(owner){
}

/**
 * @brief Fish::Fish
 * @param fishData
 */
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

/**
 * @brief Fish class deconstructor
 */
Fish::~Fish() {

}

/**
 * @brief Enables the user to edit their fish's information, performed
 *        by going from the engine class to the profile class to this function
 * @param name
 * @param age
 * @param location
 * @param species
 * @param description
 */
void Fish::edit_data(QString name, int age, QString location, QString species, QString description){
    this->name = name;
    this->age = age;
    this->location = location;
    this->species = species;
    this->description = description;
}

/**
 * @brief changes the profile pciture stored for this fish
 * @param picture
 */
void Fish::edit_picture(QByteArray picture){
    this->picture = picture;
}

/**
 * @brief checks whether a specified profile is the owner of this fish
 * @param profile
 * @return true if the param matches this fish's owner, false otherwise
 */
bool Fish::is_owner(Profile *profile){
    return profile == owner;
}

//***********GETTER METHODS*****************//
/**
 * @brief Fish::get_id
 * @return this fish's id
 */
int Fish::get_id(){
    return fishId;
}

/**
 * @brief Fish::get_ownerId
 * @return id from the profile of this fish's owner
 */
int Fish::get_ownerId(){
    return ownerId;
}

/**
 * @brief Fish::get_name
 * @return this fish's name
 */
QString Fish::get_name(){
    return name;
}

/**
 * @brief Fish::get_age
 * @return this fish's age
 */
int Fish::get_age(){
    return age;
}

/**
 * @brief Fish::get_location
 * @return this fish's location
 */
QString Fish::get_location(){
    return location;
}

/**
 * @brief Fish::get_species
 * @return this fish's species
 */
QString Fish::get_species(){
    return species;
}

/**
 * @brief Fish::get_dateCreated
 * @return day this fish was added to system
 */
QDateTime Fish::get_dateCreated(){
    return dateCreated;
}

/**
 * @brief Fish::get_description
 * @return this fish's bio
 */
QString Fish::get_description(){
    return description;
}

/**
 * @brief Fish::get_picture
 * @return this fish's profile picture
 */
QByteArray Fish::get_picture(){
    return picture;
}

/**
 * @brief Fish::get_owner
 * @return this fish's owner's profile
 */
Profile *Fish::get_owner(){
    return owner;
}
