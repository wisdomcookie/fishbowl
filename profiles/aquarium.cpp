#include "aquarium.h"
#include "fish.h"

Aquarium::Aquarium() {

}

Aquarium::Aquarium(Profile *owner): owner(owner) {

}


Aquarium::~Aquarium() {

}

void Aquarium::add_fish(Fish *fish){
    fishCollection[fish->get_id()] = fish;
}

void Aquarium::remove_fish(Fish *fish){
    fishCollection.erase(fish->get_id());
}

std::map<int, Fish*> Aquarium::get_fish(){
    return fishCollection;
}
