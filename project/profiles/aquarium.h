#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <map>
class Profile;
class Fish;

class Aquarium
{
public:
    Aquarium();
    Aquarium(Profile *owner);
    ~Aquarium();

    void add_fish(Fish *fish);
    void remove_fish(Fish *fish);

    std::map<int, Fish*> get_fish();

private:

    Profile *owner;
    std::map<int, Fish*> fishCollection;
};

#endif // AQUARIUM_H
