#include "aquarium.h"
#include "fish.h"

/**
 * @brief Empty constructor for aquarium class, was designed to hold
 *        fish within a group, but never implemented due to time
 */
Aquarium::Aquarium() {

}

/**
 * @brief Constructor for aquarium that takes an owner
 * @param owner is profile of a fish owner
 */
Aquarium::Aquarium(Profile *owner): owner(owner) {

}

/**
 * @brief deconstructor for aquarium class
 */
Aquarium::~Aquarium() {

}

/**
 * @brief Adds a fish to the aquarium
 * @param fish holds identity of fish added to aquarium
 */
void Aquarium::add_fish(Fish *fish){
    fishCollection[fish->get_id()] = fish;
}

/**
 * @brief Removes a fish from the aquarium
 * @param fish holds identity of fish removed from aquarium
 */
void Aquarium::remove_fish(Fish *fish){
    fishCollection.erase(fish->get_id());
}

/**
 * @brief Get method for the list of fish
 * @return a map of the fish and their index
 */
std::map<int, Fish*> Aquarium::get_fish(){
    return fishCollection;
}
