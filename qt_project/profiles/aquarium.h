#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <map>
class Profile;
class Fish;

class Aquarium
{
public:
    //Aquarium constructors
    Aquarium();
    Aquarium(Profile *owner);

    //Aquarium deconstructor
    ~Aquarium();

    //functions to add or remove a fish from an aquarium
    void add_fish(Fish *fish);
    void remove_fish(Fish *fish);

    //returns the map of fish in the collection
    std::map<int, Fish*> get_fish();

private:
    //current owner's profile, retrieved from second constructor
    Profile *owner;

    //map of all fish in the aquarium
    std::map<int, Fish*> fishCollection;
};

#endif // AQUARIUM_H
