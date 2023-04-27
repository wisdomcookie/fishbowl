#include "fish.h"

fish::fish() {

}

fish::fish(string name, string species, string bio) {
    this->name = name;
    this->species = species;
    this->bio = bio;
    id = owner->id;
}

fish::~fish() {

}

/**
 * The following 9 methods are for changing fish profile parameters and getter
 * methods for said parameters.
 * @brief fish::changeName
 * @param n
 */
void fish::changeName(string n) {
    name = n;
}

void fish::changeLocation(string l) {
    location = l;
}

void fish::changeBio(string b) {
    bio = b;
}

void fish::changeSpecies(string s) {
    species = s;
}

string fish::getName() {
    return name;
}

string fish::getLocation() {
    return location;
}

string fish::getSpecies() {
    return species;
}

string fish::getBio() {
    return bio;
}

profile* fish::getOwner() {
    return owner;
}


